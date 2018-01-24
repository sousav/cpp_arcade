/*
** Arcade.cpp for Shared in /Users/gmblucas/Desktop/Shared/cpp_arcade/sources
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Thu Mar 16 23:49:45 2017 Lucas Gambini
** Last update	Sun Apr 09 22:04:24 2017 Full Name
*/

#include "Arcade.hpp"

Arcade::Arcade ()
{
    _menu = new Menu();
    _isRunning = MENU;
    _currentGame = 0;
    _currentGraph = 0;
    _frameRate = 30;
    _menu->setArcade(this);
    _name = std::string("AAA");
}

std::string &Arcade::getSetName()
{
    return (this->_name);
}

Arcade::~Arcade()
{
    delete _menu;
    delete this->_currentGraph;
    for(std::vector<ScoreManager *>::iterator it=_scoreVector.begin() ; it < _scoreVector.end(); it++)
        delete (*it);
    for(std::vector<void *>::iterator it=_hanldeList.begin() ; it < _hanldeList.end(); it++)
        dlclose(*it);
}

void	Arcade::Setup()
{
    FillGraphVector();
    FillGameVector();
}

void Arcade::transfertLoad() const
{
    if (this->_isRunning == RUNNING) {
        this->_currentGraph->giveSprite(this->_currentGame->getSprite());
        this->_currentGraph->giveMusic(this->_currentGame->getMusic());
        this->_currentGraph->giveModel3D(this->_currentGame->getModel3D());
    }
}

void	Arcade::Start(std::string const &startingLib)
{
    int startIndex = 0;

    if (std::find(_libGraphName.begin(), _libGraphName.end(), startingLib) != _libGraphName.end())
        startIndex = std::distance(_libGraphName.begin(), std::find(_libGraphName.begin(), _libGraphName.end(), startingLib));
    if (_libGraph.empty() == true)
        throw NoLibGraphFound("No graphical .so found");
    this->_currentGraph = this->_libGraph[startIndex]();
    this->_currentGraphIndex = startIndex;
    this->_currentGraph->InitLib();
    this->_currentGraph->setBridge(this);
    this->_currentGraph->giveSprite(this->_menu->getSprite());
    this->_currentGraph->giveMusic(this->_menu->getMusic());
    this->_currentGraph->giveModel3D(this->_menu->getModel3D());
    this->_menu->InitGame();
}

void    Arcade::InitCurrentGame(int index)
{
    if (this->_currentGame != NULL)
        delete this->_currentGame;
    this->_currentGame = this->_libGame[index]();
    this->_currentGameIndex = index;
    this->_frameRate = this->_currentGame->getFrameRatePerSecond();
    this->_scoreVector[this->_currentGameIndex]->setName(this->getSetName());
    this->_currentGame->setScoreManager(this->_scoreVector[this->_currentGameIndex]);
    this->_currentGame->InitGame();
    this->_isRunning = RUNNING;
    transfertLoad();
}

void	Arcade::FillGraphVector()
{
    lib_ptr lptr;
    void *handle;
    void *ptr;
    std::vector<std::string> files;

    files = DirectoryManager::getFilesInDir("./lib/");
    _libGraphName = files;
    for(std::vector<std::string>::iterator it=files.begin() ; it < files.end(); it++ ) {
        handle = (ExternLib((*it).c_str(), RTLD_LAZY)).getLib();
        if (handle == NULL) {
            std::cout<<dlerror()<<std::endl;
            continue;
        }
        this->_hanldeList.push_back(handle);
        try {
            ptr = dlsym(handle, "Create");
            lptr = (lib_ptr)ptr;
            _libGraph.push_back(lptr);
        } catch (std::exception const & e) {
            std::cerr << "Function Create not found, " << e.what() << std::endl;
        };
    }
}

void	Arcade::FillGameVector()
{
    void *handle;
    void *ptr;
    game_ptr gptr;
    std::vector<std::string> files;
    std::vector<std::string> trueFile;
    std::string str;
    ScoreManager *score;
    size_t found;

    files = DirectoryManager::getFilesInDir("./games/");
    for(std::vector<std::string>::iterator it=files.begin() ; it < files.end(); it++ ) {
        handle = (ExternLib((*it).c_str(), RTLD_LAZY)).getLib();
        if (handle == NULL) {
            std::cout<<dlerror()<<std::endl;
            continue;
        }
        this->_hanldeList.push_back(handle);
        ptr = dlsym(handle, "Create");
        gptr = (game_ptr)ptr;
        _libGame.push_back(gptr);
        trueFile.push_back(*it);
        str = *it;
        if ((found = str.rfind(".so")) != std::string::npos && found == str.size() - 3)
            str = str.substr(0, found);
        score = new ScoreManager(str, _name);
        _scoreVector.push_back(score);
    }
    this->_menu->setGames(trueFile);
    this->_menu->setScoreVector(_scoreVector);
}

void	Arcade::mainLoop()
{
    std::chrono::time_point<std::chrono::system_clock> start, end;

    while (this->_isRunning != EXIT) {
        start = std::chrono::system_clock::now();

        this->transfertData();
        if (this->_isRunning == RUNNING)
            this->_currentGame->play();
        else
            this->_menu->play();
        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        int x = (1000 / this->_frameRate) - (elapsed.count() / 1000);
        std::this_thread::sleep_for(std::chrono::milliseconds(x));
    }
}

void	Arcade::toggleRunning()
{
    if (_isRunning == RUNNING)
        _isRunning = MENU;
    else
        _isRunning = RUNNING;
}

void	Arcade::prevGraph()
{
    delete _currentGraph;
    _currentGraphIndex = _currentGraphIndex == 0 ? (int)_libGraph.size() - 1 : _currentGraphIndex - 1;
    _currentGraph = _libGraph[_currentGraphIndex]();
    this->_currentGraph->InitLib();
    transfertLoad();
    this->_currentGraph->setBridge(this);
}

void	Arcade::nextGraph()
{
    delete _currentGraph;
    _currentGraphIndex = _currentGraphIndex == (int)_libGraph.size() - 1 ? 0 : _currentGraphIndex + 1;
    _currentGraph = _libGraph[_currentGraphIndex]();
    this->_currentGraph->InitLib();
    transfertLoad();
    this->_currentGraph->setBridge(this);
}

void	Arcade::prevGame()
{
    if (this->_isRunning == RUNNING)
    {
        delete _currentGame;
        _currentGameIndex = _currentGameIndex == 0 ? _libGame.size() : _currentGameIndex;
        _currentGameIndex = (_currentGameIndex - 1) % _libGame.size();
        _currentGame = _libGame[_currentGameIndex]();
        this->_scoreVector[this->_currentGameIndex]->setName(this->getSetName());
        this->_currentGame->setScoreManager(this->_scoreVector[this->_currentGameIndex]);
        transfertLoad();
        this->_currentGame->InitGame();
        this->_frameRate = this->_currentGame->getFrameRatePerSecond();
    }
}

void	Arcade::nextGame()
{
    if (this->_isRunning == RUNNING)
    {
        delete _currentGame;
        _currentGameIndex = (_currentGameIndex + 1) % _libGame.size();
        _currentGame = _libGame[_currentGameIndex]();
        this->_scoreVector[this->_currentGameIndex]->setName(this->getSetName());
        this->_currentGame->setScoreManager(this->_scoreVector[this->_currentGameIndex]);
        transfertLoad();
        this->_currentGame->InitGame();
        this->_frameRate = this->_currentGame->getFrameRatePerSecond();
    }
}

void	Arcade::goUp() const
{
    this->_isRunning == RUNNING ? this->_currentGame->goUp() : this->_menu->goUp();
}

void	Arcade::goDown() const
{
    this->_isRunning == RUNNING ? this->_currentGame->goDown() : this->_menu->goDown();
}

void	Arcade::goLeft() const
{
    this->_isRunning == RUNNING ? this->_currentGame->goLeft() : this->_menu->goLeft();
}

void	Arcade::goRight() const
{
    this->_isRunning == RUNNING ? this->_currentGame->goRight() : this->_menu->goRight();
}

void	Arcade::goForward() const
{
    this->_isRunning == RUNNING ? this->_currentGame->goForward() : this->_menu->goForward();
}

void	Arcade::shoot() const
{
    this->_isRunning == RUNNING ? this->_currentGame->shoot() : this->_menu->shoot();
}

void	Arcade::pressEchap()
{
    if (this->_currentGame != NULL)
        delete this->_currentGame;
    this->_isRunning = EXIT;
}

void Arcade::pressEight()
{
    if (this->_isRunning == RUNNING)
        InitCurrentGame(this->_currentGameIndex);
}

void Arcade::pressNine()
{
    if (this->_isRunning == RUNNING)
    {
        this->_isRunning = MENU;
        if (this->_currentGame != NULL)
        {
            delete this->_currentGame;
            this->_currentGame = NULL;
        }
        this->_currentGraph->giveSprite(this->_menu->getSprite());
        this->_currentGraph->giveMusic(this->_menu->getMusic());
        this->_currentGraph->giveModel3D(this->_menu->getModel3D());
    }
}

void	Arcade::transfertData() const
{
    std::vector <AData *> values = this->_isRunning == RUNNING ? this->_currentGame->getData() : this->_menu->getData();
    std::sort(values.begin(), values.end(), [](AData *a, AData *b ) {
        AVisual *tmp1 = dynamic_cast<AVisual *>(a);
        AVisual *tmp2 = dynamic_cast<AVisual *>(b);
        if (tmp1 == NULL || tmp2 == NULL) {
            return false;
        }
        return tmp1->getZIndex() < tmp2->getZIndex();
    });
    this->_currentGraph->giveData(values);
}

Arcade::Arcade(const Arcade &obj)
{
    _isRunning = obj._isRunning;
}

Arcade	&Arcade::operator=(const Arcade &obj)
{
    this->_isRunning = obj._isRunning;
    this->_frameRate = obj._frameRate;
    this->_currentGraph = obj._currentGraph;
    this->_currentGame = obj._currentGame;
    this->_libGraph = obj._libGraph;
    this->_libGame = obj._libGame;
    //this->_scoreVector = obj._scoreVector;
    return *this;
}
