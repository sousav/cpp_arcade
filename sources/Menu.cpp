//
// Menu.cpp for menu in /Users/leandr_g/Documents/Shared folder/cpp_arcade/sources/
//
// Made by Gaëtan Léandre
// Login   <leandr_g@epitech.eu>
//
// Started on  Wed Apr  5 16:57:05 2017 Gaëtan Léandre
// Last update Sun Apr  9 01:10:08 2017 Gaëtan Léandre
//

#include    "Menu.hpp"

Menu::~Menu()
{
    for(std::vector<Text *>::iterator it=this->_highscore.begin() ; it < this->_highscore.end(); it++ )
        delete (*it);
    for(std::vector<Text *>::iterator it=this->_games.begin() ; it < this->_games.end(); it++ )
        delete (*it);
    for(std::vector<Text *>::iterator it=this->_ctn.begin() ; it < this->_ctn.end(); it++ )
        delete (*it);
    for(std::vector<Text *>::iterator it=this->_nameVec.begin() ; it < this->_nameVec.end(); it++ )
        delete (*it);
    if (this->_title)
        delete this->_title;
    if (this->_earth)
        delete this->_earth;
    delete this->_background;
}

Menu::Menu()
{
    Text *txt;

    this->_title = NULL;
    this->_earth = NULL;
    this->_name = std::string("Menu");
    this->_spriteList.push_back(std::string("./Assets/Sprites/earth.png"));
    this->_modelList.push_back(std::string("./Assets/Models/earth.obj"));
    this->_arc = NULL;
    this->_choice = NAME;
    this->_background = new Cube(Position(0, 0, 0), Position(100, 100, 1), Texture("", Color(50, 50, 50, 255), 0), 0);
    this->_dataGame.push_back(this->_background);
    txt = new Text(std::string("Return"), 40, Position (0, 95), 99);
    txt->setTexture(Texture(Color(255, 255, 255, 255)));
    txt->setAlign(Text::Align::LEFT);
    this->_ctn.push_back(txt);
    txt = new Text(std::string("> Continue <"), 40, Position (100, 95), 99);
    txt->setTexture(Texture(Color(255, 0, 0, 255)));
    txt->setAlign(Text::Align::RIGHT);
    this->_ctn.push_back(txt);
    this->_ctnPos = 1;
    this->_pos = 0;
}

void Menu::InitGame()
{
    Text *txt;

    this->_nameVec.clear();
    this->_dataName.clear();
    this->_dataName.push_back(this->_background);
    txt = new Text("^  ", 100, Position (50, 45), 99);
    txt->setTexture(Texture(Color(255, 255, 255, 255)));
    txt->setAlign(Text::Align::CENTER);
    this->_nameVec.push_back(txt);
    this->_dataName.push_back(txt);
    txt = new Text(this->_arc->getSetName(), 100, Position (50, 50), 99);
    txt->setTexture(Texture(Color(255, 255, 255, 255)));
    txt->setAlign(Text::Align::CENTER);
    this->_nameVec.push_back(txt);
    this->_dataName.push_back(txt);
    txt = new Text("v  ", 100, Position (50, 57), 99);
    txt->setTexture(Texture(Color(255, 255, 255, 255)));
    txt->setAlign(Text::Align::CENTER);
    this->_nameVec.push_back(txt);
    this->_dataName.push_back(txt);
    this->_posName = 0;
    this->_choice = NAME;
    txt = new Text("Select your pseudo", 90, Position (50, 5), 99);
    txt->setTexture(Texture(Color(255, 255, 255, 255)));
    txt->setAlign(Text::Align::CENTER);
    this->_nameVec.push_back(txt);
    this->_dataName.push_back(txt);
}

std::string const &Menu::getGameName() const
{
    return this->_name;
}

int Menu::getFrameRatePerSecond() const
{
    return (60);
}

std::vector <AData *> const &Menu::getData() const
{
    if (this->_choice == GAME)
        return this->_dataGame;
    else if (this->_choice == HIGHSCORE)
        return this->_dataHigh;
    return this->_dataName;
}

std::vector <std::string> const & Menu::getSprite() const
{
    return this->_spriteList;
}

std::vector <std::string> const & Menu::getMusic() const
{
    return this->_musicList;
}

std::vector <std::string> const & Menu::getModel3D() const
{
    return this->_modelList;
}

void Menu::setScoreManager(ScoreManager *scoreManager)
{
    (void)scoreManager;
}

void Menu::updateNewScore() const
{
}

void Menu::play()
{
    if (this->_earth != NULL) {
        this->_earth->setRotation(this->_earth->getTexture().getRotation() + 1);
    }
}

void Menu::getMap()
{
}

void Menu::whereIAm()
{
}

void Menu::goUp()
{
    std::string str;

    if (this->_choice == GAME)
    {
        str = this->_games[this->_pos]->getText();
        this->_games[this->_pos]->setTexture(Texture(Color(255, 255, 255, 255)));
        this->_games[this->_pos]->setText(str.substr(2, str.size() - 4));
        if (this->_pos == 0)
            this->_pos = this->_games.size() - 1;
        else
            this->_pos--;
        this->_games[this->_pos]->setTexture(Texture(Color(255, 0, 0, 255)));
        this->_games[this->_pos]->setText(std::string("> ") + this->_games[this->_pos]->getText() + std::string(" <"));
    }
    else if (this->_choice == NAME)
    {
        if (this->_arc->getSetName()[this->_posName] == 'Z')
            this->_arc->getSetName()[this->_posName] = 'A';
        else
            this->_arc->getSetName()[this->_posName] = this->_arc->getSetName()[this->_posName] + 1;
        this->_nameVec[1]->setText(this->_arc->getSetName());
    }
}

void Menu::goDown()
{
    std::string str;

    if (this->_choice == GAME)
    {
        str = this->_games[this->_pos]->getText();
        this->_games[this->_pos]->setTexture(Texture(Color(255, 255, 255, 255)));
        this->_games[this->_pos]->setText(str.substr(2, str.size() - 4));    this->_pos++;
        if (this->_pos >= this->_games.size())
            this->_pos = 0;
        this->_games[this->_pos]->setTexture(Texture(Color(255, 0, 0, 255)));
        this->_games[this->_pos]->setText(std::string("> ") + this->_games[this->_pos]->getText() + std::string(" <"));
    }
    else if (this->_choice == NAME)
    {
        if (this->_arc->getSetName()[this->_posName] == 'A')
            this->_arc->getSetName()[this->_posName] = 'Z';
        else
            this->_arc->getSetName()[this->_posName] = this->_arc->getSetName()[this->_posName] - 1;
        this->_nameVec[1]->setText(this->_arc->getSetName());
    }
}

void Menu::goLeft()
{
    std::string str;

    if (this->_choice == HIGHSCORE)
    {
        str = this->_ctn[this->_ctnPos]->getText();
        this->_ctn[this->_ctnPos]->setTexture(Texture(Color(255, 255, 255, 255)));
        this->_ctn[this->_ctnPos]->setText(str.substr(2, str.size() - 4));
        if (this->_ctnPos == 0)
            this->_ctnPos = 1;
        else
            this->_ctnPos = 0;
        this->_ctn[this->_ctnPos]->setTexture(Texture(Color(255, 0, 0, 255)));
        this->_ctn[this->_ctnPos]->setText(std::string("> ") + this->_ctn[this->_ctnPos]->getText() + std::string(" <"));
    }
    else if (this->_choice == NAME)
    {
        str = "   ";
        if (this->_posName == 0)
            this->_posName = 2;
        else
            this->_posName--;
        str[this->_posName] = '^';
        this->_nameVec[0]->setText(str);
        str[this->_posName] = 'v';
        this->_nameVec[2]->setText(str);
    }
}

void Menu::goRight()
{
    std::string str;

    if (this->_choice == HIGHSCORE)
    {
        str = this->_ctn[this->_ctnPos]->getText();
        this->_ctn[this->_ctnPos]->setTexture(Texture(Color(255, 255, 255, 255)));
        this->_ctn[this->_ctnPos]->setText(str.substr(2, str.size() - 4));
        if (this->_ctnPos == 0)
            this->_ctnPos = 1;
        else
            this->_ctnPos = 0;
        this->_ctn[this->_ctnPos]->setTexture(Texture(Color(255, 0, 0, 255)));
        this->_ctn[this->_ctnPos]->setText(std::string("> ") + this->_ctn[this->_ctnPos]->getText() + std::string(" <"));
    }
    else if (this->_choice == NAME)
    {
        str = "   ";
        this->_posName = (this->_posName + 1) % 3;
        str[this->_posName] = '^';
        this->_nameVec[0]->setText(str);
        str[this->_posName] = 'v';
        this->_nameVec[2]->setText(str);
    }
}

void Menu::goForward()
{
    std::vector<Score> score;
    Text *txt;
    size_t i;

    i = 0;
    if (this->_choice == GAME)
    {
        if (this->_pos < this->_games.size() - 1)
        {
            for(std::vector<Text *>::iterator it=this->_highscore.begin() ; it < this->_highscore.end(); it++ )
                delete (*it);
            this->_highscore.clear();
            this->_dataHigh.clear();
            this->_dataHigh.push_back(this->_background);
            txt = new Text(std::string("HighScores"), 60, Position (50, 5), 99);
            txt->setTexture(Texture(Color(255, 255, 255, 255)));
            txt->setAlign(Text::Align::CENTER);
            this->_highscore.push_back(txt);
            this->_dataHigh.push_back(txt);
            score = this->_scoreVector[this->_pos]->getScoreBoard();
            std::sort(score.begin(), score.end(), [](Score a, Score b ) {
                return a.score > b.score;
            });
            while (i < 10 && i < score.size())
            {
                txt = new Text(score[i].name + std::string(" : ") + std::to_string(score[i].score), 40, Position (50, 15 + (70 / 10 * i) + (7 / 2)), 99);
                txt->setTexture(Texture(Color(255, 255, 255, 255)));
                txt->setAlign(Text::Align::CENTER);
                this->_highscore.push_back(txt);
                this->_dataHigh.push_back(txt);
                i++;
            }
            this->_dataHigh.push_back(this->_ctn[0]);
            this->_dataHigh.push_back(this->_ctn[1]);
            this->_choice = HIGHSCORE;
        }
        else if (this->_arc)
        {
            for(std::vector<Text *>::iterator it=this->_nameVec.begin() ; it < this->_nameVec.end(); it++)
                delete (*it);
            this->_nameVec.clear();
            this->_dataName.clear();
            this->_dataName.push_back(this->_background);
            txt = new Text("^  ", 100, Position (50, 45), 99);
            txt->setTexture(Texture(Color(255, 255, 255, 255)));
            txt->setAlign(Text::Align::CENTER);
            this->_nameVec.push_back(txt);
            this->_dataName.push_back(txt);
            txt = new Text(this->_arc->getSetName(), 100, Position (50, 50), 99);
            txt->setTexture(Texture(Color(255, 255, 255, 255)));
            txt->setAlign(Text::Align::CENTER);
            this->_nameVec.push_back(txt);
            this->_dataName.push_back(txt);
            txt = new Text("v  ", 100, Position (50, 57), 99);
            txt->setTexture(Texture(Color(255, 255, 255, 255)));
            txt->setAlign(Text::Align::CENTER);
            this->_nameVec.push_back(txt);
            this->_dataName.push_back(txt);
            this->_posName = 0;
            this->_choice = NAME;
            txt = new Text("Select your pseudo", 90, Position (50, 5), 99);
            txt->setTexture(Texture(Color(255, 255, 255, 255)));
            txt->setAlign(Text::Align::CENTER);
            this->_nameVec.push_back(txt);
            this->_dataName.push_back(txt);
        }
    }
    else if (this->_choice == HIGHSCORE)
    {
        if (this->_ctnPos == 0)
        {
            this->_choice = GAME;
            this->_ctn[this->_ctnPos]->setTexture(Texture(Color(255, 255, 255, 255)));
            this->_ctn[this->_ctnPos]->setText("Return");
            this->_ctnPos = 1;
            this->_ctn[this->_ctnPos]->setTexture(Texture(Color(255, 0, 0, 255)));
            this->_ctn[this->_ctnPos]->setText(std::string("> ") + this->_ctn[this->_ctnPos]->getText() + std::string(" <"));
        }
        else if (this->_arc)
        {
            this->_choice = GAME;
            _arc->InitCurrentGame(this->_pos);
        }
    }
    else if (this->_choice == NAME)
        this->_choice = GAME;
}

void Menu::shoot()
{
}

void Menu::setGames(std::vector <std::string>  const &file)
{
    std::size_t found;
    std::string str;
    Text *txt;
    size_t pos;

    pos = 0;
    for(std::vector<std::string>::const_iterator it=file.begin() ; it < file.end(); it++ )
    {
        str = *it;
        if ((found = str.find_last_of("/\\")) != std::string::npos)
            str = str.substr(found + 1);
        if ((found = str.rfind(".so")) != std::string::npos && found == str.size() - 3)
            str = str.substr(0, found);
        if ((found = str.rfind("libarcade_")) != std::string::npos && found == 0)
            str = str.substr(10, str.size());
        txt = new Text(str, 40, Position (50, 15 + (70 / file.size() * pos) + (70 / file.size() / 2)), 99);
        txt->setAlign(Text::Align::CENTER);
        if (pos == this->_pos)
        {
            txt->setTexture(Texture(Color(255, 0, 0, 255)));
            txt->setText(std::string("> ") + str + std::string(" <"));
        }
        else
            txt->setTexture(Texture(Color(255, 255, 255, 255)));
        this->_games.push_back(txt);
        this->_dataGame.push_back(txt);
        pos++;
    }
    txt = new Text(std::string("Change name"), 40, Position (0, 95), 99);
    txt->setTexture(Texture(Color(255, 255, 255, 255)));
    txt->setAlign(Text::Align::LEFT);
    this->_games.push_back(txt);
    this->_dataGame.push_back(txt);
    _title = new Text("Arcade sourciliere", 90, Position (50, 5), 99);
    _title->setTexture(Texture(Color(255, 255, 255, 255)));
    _title->setAlign(Text::Align::CENTER);
    this->_dataGame.push_back(_title);
    this->_earth = new Sphere(Position(7,10,10) , 15, Texture("./Assets/Sprites/earth.png", Color(50, 50, 255, 255), 0, Model3D("./Assets/Models/earth.obj", Position(10, 25, 0), Position(3,3,3), Position())), 50);
    this->_dataGame.push_back(this->_earth);
}

void Menu::setScoreVector(std::vector<ScoreManager *> const &scoreVector)
{
    this->_scoreVector = scoreVector;
}

void Menu::setArcade(Arcade *arc)
{
    this->_arc = arc;
}
