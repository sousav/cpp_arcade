//
// NcursesWrapper.cpp for  in /home/gambin_l/Shared/cpp_arcade/lib/NCurses
//
// Made by lucas gambini
// Login   <gambin_l@epitech.net>
//
// Started on  Thu Mar 16 18:43:22 2017 lucas gambini
// Last update Sun Apr  9 22:10:12 2017 Gaëtan Léandre
//

#include "IGraph.hpp"

#include "NCursesWrapper.hpp"

NCursesWrapper::NCursesWrapper() {
    this->_height = 50;
    this->_width = 100;
    this->_libName = std::string("lib_arcade_ncurses.so");
}

NCursesWrapper::~NCursesWrapper() {
    endwin();
}

void NCursesWrapper::InitLib() {
    WINDOW *w = initscr();
    nodelay(w, TRUE);
    curs_set(0);
    keypad(stdscr, TRUE);
    this->createColors();
}

std::string const & NCursesWrapper::getLibName() const {
    return this->_libName;
}

void NCursesWrapper::setColor(Color const &col)
{
    unsigned char r = col.getR();
    unsigned char g = col.getG();
    unsigned char b = col.getB();

    if (r >= g + 30 && r >= b + 30)
        attron(COLOR_PAIR(3));
    else if (g >= r + 30 && g >= b + 30)
        attron(COLOR_PAIR(5));
    else if (b >= r + 30 && b >= g + 30)
        attron(COLOR_PAIR(2));
    else if (r >= g + 30)
        attron(COLOR_PAIR(7));
    else if (r >= b + 30)
        attron(COLOR_PAIR(6));
    else if (g >= r + 30)
        attron(COLOR_PAIR(7));
    else if (r > 50 && g > 50 && b > 50)
        attron(COLOR_PAIR(1));
    else
        attron(COLOR_PAIR(8));
}

void NCursesWrapper::createColors()
{
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    init_pair(2, COLOR_BLUE, COLOR_BLUE);
    init_pair(3, COLOR_RED, COLOR_RED);
    init_pair(4, COLOR_CYAN, COLOR_CYAN);
    init_pair(5, COLOR_GREEN, COLOR_GREEN);
    init_pair(6, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(7, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(8, COLOR_BLACK, COLOR_BLACK);
    init_pair(9, COLOR_WHITE, COLOR_BLACK);
    init_pair(10, COLOR_BLACK, COLOR_WHITE);
}

void NCursesWrapper::drawSquare()
{
    unsigned int i;
    unsigned int j;

    i = 0;
    j = 0;
    attron(COLOR_PAIR(1));
    while (i < this->_width + 2)
    {
        j = 0;
        while (j < this->_height + 2)
        {
            if (j == 0 || i == 0 || i == this->_width + 1 || j == this->_height + 1)
                mvprintw(j, i, " ");
            j++;
        }
        i++;
    }
    attron(COLOR_PAIR(9));
}

void NCursesWrapper::giveData(std::vector <AData *> const &datas) {
    char c = getch();
    if (this->handleEvent(c) == 1)
        return;
    erase();
    for(auto const& data: datas) {
        this->handleData(*data);
    }
    this->drawSquare();
    refresh();
}

void NCursesWrapper::giveSprite(std::vector <std::string> const &spriteList) {
    (void)spriteList;
}

void NCursesWrapper::giveMusic(std::vector <std::string> const &musicList)
{
    (void)musicList;
}
void NCursesWrapper::giveModel3D(std::vector <std::string> const &modelList)
{
    (void)modelList;
}

void NCursesWrapper::setBridge(IArcadeBridge * bridge) {
    this->_bridge = bridge;
}

int NCursesWrapper::handleEvent(int event) {
    switch (event)
    {
            case 'p':
                this->toggleRunning();
                break;
            case 27:
                this->pressEchap();
                break;
            case ' ':
                this->shoot();
                break;
            case 10:
                this->goForward();
                break;
            case 4:
                this->goLeft();
                break;
            case 5:
                this->goRight();
                break;
            case 3:
                this->goUp();
                break;
            case 2:
                this->goDown();
                break;
            case 50:
                this->prevGraph();
                return (1);
                break;
            case 51:
                this->nextGraph();
                return (1);
                break;
            case 52:
                this->prevGame();
                return (1);
                break;
            case 53:
                this->nextGame();
                return (1);
                break;
            case 56:
                this->pressEight();
                return (1);
                break;
            case 57:
                this->pressNine();
                return (1);
                break;
            default:
                break;
    }
    return (0);
}

void NCursesWrapper::handleData(AData const & data) {
    switch (data.getShape()) {
        case DataType::Sphere:
            this->handleSphere(data);
            break;
        case DataType::Cube:
            this->handleCube(data);
            break;
        case DataType::Camera:
            this->handleCamera(data);
            break;
        case DataType::Light:
            this->handleLight(data);
            break;
        case DataType::Music:
            this->handleMusic(data);
            break;
        case DataType::Text:
            this->handleText(data);
            break;
    }
}

void NCursesWrapper::handleSphere(AData const & data) {
    try
    {
        Sphere const & sphere = dynamic_cast<Sphere const &>(data);
        int centerX = sphere.getPosition().getX();
        int centerY = sphere.getPosition().getY();
        int radius = sphere.getRadius();

        this->setColor(sphere.getTexture().getColor());
        for(int i = 0; i<100;i++)
        {
            for(int j = 0;j<100;j++)
            {
                if ((i - centerX) * (i - centerX) + (j - centerY) * (j - centerY) <= radius * radius)
                    mvprintw((int)((j / 100.0) * this->_height + 1), (int)((i / 100.0) * this->_width + 1), " ");
            }
        }
        attron(COLOR_PAIR(9));
    } catch (std::exception const &e){
        std::cerr << e.what() << std::endl;
    }
}

void NCursesWrapper::handleCube(AData const & data) {
    try
    {
        Cube const & cube = dynamic_cast<Cube const &>(data);
        int i;
        int x = (cube.getPosition().getX() / 100.0) * this->_width + 1;
        int y = (cube.getPosition().getY() / 100.0) * this->_height + 1;
        float toXfloat = (cube.getSize().getX() / 100.0) * this->_width;
        float toYfloat = (cube.getSize().getY() / 100.0) * this->_height;
        int toX = x + (toXfloat > (int)toXfloat ? toXfloat + 1 : toXfloat);
        int toY = y + (toYfloat > (int)toYfloat ? toYfloat + 1 : toYfloat);
        this->setColor(cube.getTexture().getColor());
        while (x < toX)
        {
            i = y;
            while (i < toY)
            {
                mvprintw(i, x, " ");
                i++;
            }
            x++;
        }
        attron(COLOR_PAIR(9));
    } catch (std::exception const &e){
        std::cerr << e.what() << std::endl;
    }
}

void NCursesWrapper::handleCamera(AData const & data) {
    (void)data;
}

void NCursesWrapper::handleLight(AData const & data) {
    (void)data;
}

void NCursesWrapper::handleMusic(AData const & data) {
    try
    {
        Audio const & audio = dynamic_cast<Audio const &>(data);
        if (audio.getRepeat() == false)
            beep();
    } catch (std::exception const &e){
        std::cerr << e.what() << std::endl;
    }
}

void NCursesWrapper::handleText(AData const & data) {
    try
    {
        Text const & text = dynamic_cast<Text const &>(data);
        std::string str = text.getText();
        int x = (text.getPosition().getX() / 100.0) * this->_width + 1;
        int y = (text.getPosition().getY() / 100.0) * this->_height + 1;
        if (text.getAlign() == Text::Align::CENTER)
            x -= (str.size() / 2);
        else if (text.getAlign() == Text::Align::RIGHT)
            x -= str.size();
        mvprintw(y, x, str.c_str());
    } catch (std::exception const &e){
        std::cerr << e.what() << std::endl;
    }
}


void NCursesWrapper::toggleRunning() const {
    this->_bridge->toggleRunning();
}

void NCursesWrapper::prevGraph() const {
    this->_bridge->prevGraph();
}

void NCursesWrapper::nextGraph() const {
    this->_bridge->nextGraph();
}

void NCursesWrapper::prevGame() const {
    this->_bridge->prevGame();
}

void NCursesWrapper::nextGame() const {
    this->_bridge->nextGame();
}

void NCursesWrapper::goUp() const {
    this->_bridge->goUp();
}

void NCursesWrapper::goDown() const {
    this->_bridge->goDown();
}

void NCursesWrapper::goLeft() const {
    this->_bridge->goLeft();
}

void NCursesWrapper::goRight() const {
    this->_bridge->goRight();
}

void NCursesWrapper::goForward() const {
    this->_bridge->goForward();
}

void NCursesWrapper::shoot() const {
    this->_bridge->shoot();
}

void NCursesWrapper::pressEchap() const {
    this->_bridge->pressEchap();
}

void NCursesWrapper::pressEight() const {
    this->_bridge->pressEight();
}

void NCursesWrapper::pressNine() const {
    this->_bridge->pressNine();
}

extern "C" {

    IGraph *Create() {
        std::cout << "Created Lib NCurses" << std::endl;
        return (new NCursesWrapper());
    }

}
