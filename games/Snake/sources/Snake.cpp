
// Snake.cpp for  in /home/gambin_l/Shared/cpp_arcade/Game/Snake
//
// Made by lucas gambini
// Login   <gambin_l@epitech.net>
//
// Started on  Thu Mar 16 17:31:41 2017 lucas gambini
// Last update Sun Apr  9 01:27:51 2017 Sousa Victor
//

#include "Snake.hpp"

Snake::Snake() {
    this->_gameName = std::string("Snake! :D");
    this->_frameRate = 60;
    this->_karcadeMode = false;
    this->_scoreManager = NULL;
    this->_scoreUpdated = false;

    this->_spriteList.push_back("./Assets/Sprites/snake_head.png");
    this->_spriteList.push_back("./Assets/Sprites/snake_body.png");
    this->_spriteList.push_back("./Assets/Sprites/snake_apple.png");

    this->_musicList.push_back("./Assets/Sounds/snake_eat.wav");
    this->_musicList.push_back("./Assets/Sounds/snake_death.wav");

    this->_modelList.push_back("./Assets/Models/Street environment_V01.obj");
    this->_modelList.push_back("./Assets/Models/spider.obj");
    this->_modelList.push_back("./Assets/Models/apple textured obj.obj");
}

Snake::~Snake () {
    delete this->_background;
}

void Snake::InitGame() {
    this->_background = new Cube(Position(0, 0, 0), Position(100, 100, 5), Texture("", Color(50, 50, 50, 255), 0, Model3D("./Assets/Models/Street environment_V01.obj", Position(-10, 1, 2), Position(3, 3, 3), Position(90, 180, 0))), 0);
    this->_data.push_back(this->_background);
    this->_snake = new SnakeBody(Position(50, 50, 5), &this->_data, this->_karcadeMode);
    this->_scoreText = new Text(std::string("Score: ") + std::to_string(this->_snake->getScore()), 40, Position (1, 1), 99);
    this->_scoreText->setTexture(Texture(Color(255, 255, 255, 255)));
    this->_gameoverText = new Text(std::string(""), 50, Position (50, 50), 99);
    this->_gameoverText->setTexture(Texture(Color(255, 255, 255, 255)));
    this->_gameoverText->setAlign(Text::Align::CENTER);
    this->_data.push_back(this->_scoreText);
    this->_data.push_back(this->_gameoverText);
    Light *light;
    light = new Light(Position(0, 0, 5));
    this->_lightList.push_back(light);
    this->_data.push_back(light);
}

std::string const & Snake::getGameName() const {
    return this->_gameName;
}

int Snake::getFrameRatePerSecond() const {
    return this->_frameRate;
}

std::vector <AData *> const & Snake::getData() const {
    return this->_data;
}


std::vector <std::string> const & Snake::getSprite() const {
    return this->_spriteList;
}
std::vector <std::string> const & Snake::getMusic() const {
    return this->_musicList;
}
std::vector <std::string> const & Snake::getModel3D() const {
    return this->_modelList;
}


void Snake::setScoreManager(ScoreManager *scoreManager) {
    this->_scoreManager = scoreManager;
}

void Snake::updateNewScore() const {
    if (this->_scoreManager)
        this->_scoreManager->pushNewScore(this->_snake->getScore());
}


void Snake::play() {
    this->_snake->Play();
    this->_scoreText->setText(std::string("Score: ") + std::to_string(this->_snake->getScore()));
    if (this->_snake->isAlive() == false) {
        this->_scoreText->setPosition(Position(50, 55));
        this->_scoreText->setAlign(Text::Align::CENTER);
        this->_gameoverText->setText(std::string("GameOver!!"));
        if (this->_scoreUpdated == false)
        {
            this->_scoreUpdated = true;
            updateNewScore();
        }
    }
    else
        this->_scoreUpdated = false;
}

void Snake::getMap() {
    arcade::GetMap *map;
	map = reinterpret_cast<struct arcade::GetMap*>(new char[sizeof(struct arcade::GetMap) + sizeof(arcade::TileType) * (20 * 20)]);

	map->type = arcade::CommandType::GET_MAP;
	map->width = 20;
	map->height = 20;

    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 20; x++) {
            map->tile[x + y * 20] = findBlockAt(x, y);
        }
    }

	write(1, map, sizeof(struct arcade::GetMap) + sizeof(arcade::TileType) * (20 * 20));
}

arcade::TileType Snake::findBlockAt(int x, int y) const {
    return this->_snake->findBlockAt(x, y);
}

void Snake::whereIAm() {
    arcade::WhereAmI *me;
	me = reinterpret_cast<struct arcade::WhereAmI *>(new char[sizeof(struct arcade::WhereAmI) + sizeof(struct arcade::Position)]);
	me->type = arcade::CommandType::WHERE_AM_I;
	me->lenght = 1;
	me->position[0].x = this->_snake->getHeadPosition().getX() / 5;
	me->position[0].y = this->_snake->getHeadPosition().getY() / 5;
	write(1, me, sizeof(struct arcade::WhereAmI) + sizeof(struct arcade::Position));
}

void Snake::goUp() {
    this->_snake->goUp();
}

void Snake::goDown() {
    this->_snake->goDown();
}

void Snake::goLeft() {
    this->_snake->goLeft();
}

void Snake::goRight() {
    this->_snake->goRight();
}

void Snake::goForward() {

}

void Snake::shoot() {

}

void Snake::setKarcadeMode(bool mode) {
    this->_karcadeMode = mode;
}

extern "C" {

    IGame *Create()
    {
        return new Snake();
    }

    void switch1(Snake &snake, arcade::CommandType const input)
    {
        switch ((uint16_t)input)
        {
            case 0:
                snake.whereIAm();
                break;
            case 1:
                snake.getMap();
                break;
            case 2:
                snake.goUp();
                break;
            case 3:
                snake.goDown();
                break;
            default:
                break;
        }
    }

    void switch2(Snake &snake, arcade::CommandType const input)
    {
        switch ((uint16_t)input)
        {
            case 4:
                snake.goLeft();
                break;
            case 5:
                snake.goRight();
                break;
            case 6:
                snake.goForward();
                break;
            case 7:
                snake.shoot();
                break;
            case 9:
                snake.play();
                break;
            default:
                break;
        }
    }

    void Play()
    {
        Snake snake;
        snake.setKarcadeMode(true);
        snake.InitGame();
        arcade::CommandType input;
        while (read(0, &input, sizeof(arcade::CommandType)))
        {
            switch1(snake, input);
            switch2(snake, input);
        }
    }

}
