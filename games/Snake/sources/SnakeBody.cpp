//
// Snake.cpp for  in /home/gambin_l/Shared/cpp_arcade/Game/Snake
//
// Made by lucas gambini
// Login   <gambin_l@epitech.net>
//
// Started on  Thu Mar 16 17:31:41 2017 lucas gambini
// Last update Sun Apr  9 22:20:59 2017 Gaëtan Léandre
//

#include "SnakeBody.hpp"

SnakeBody::SnakeBody(Position const &startingPos, std::vector <AData *> *data, bool mode) {
    this->_karcadeMode = mode;
    this->_gameData = data;
    this->_direction = 0;
    this->_nextDirection = 0;
    this->_prevDirection = 0;
    this->_camera = new Camera(Position(0, 0, 35), 45, -35);
    this->_gameData->push_back(this->_camera);
    this->_head = new Sphere(startingPos, 2.5, Texture("./Assets/Sprites/snake_head.png", Color(255, 255, 255, 255), 0, Model3D("./Assets/Models/spider.obj", Position(-0.5, -0.5, -2), Position(0.05, 0.05, 0.05), Position(90, 180, 0))), 5);
    this->_gameData->push_back(this->_head);
    this->_head->setRotation(180);
    this->_apple = new Cube(Position((this->_randGenerator.getRand() % 19) * 5, (this->_randGenerator.getRand() % 19) * 5, 5), Position(5, 5, 5), Texture("./Assets/Sprites/snake_apple.png", Color(200, 25, 25, 255), 0, Model3D("./Assets/Models/apple textured obj.obj", Position(0, 0, -3.5), Position(0.075, 0.075, 0.075), Position(90, 0, 0))));
    this->_gameData->push_back(this->_apple);
    Cube *tmp = new Cube(Position(this->_head->getPosition().getX() + 5,
                            this->_head->getPosition().getY(), 5),
                            Position(5, 5, 5), Texture("./Assets/Sprites/snake_body.png", Color(200, 200, 200, 255), 0, Model3D("./Assets/Models/spider.obj", Position(-0.5, -0.5, -2), Position(0.025, 0.025, 0.025), Position(90, 180, 0))), 3);
    this->_body.push_back(tmp);
    this->_gameData->push_back(tmp);
    tmp = new Cube(Position(this->_head->getPosition().getX() + 10,
                            this->_head->getPosition().getY(), 5),
                            Position(5, 5, 5), Texture("./Assets/Sprites/snake_body.png", Color(200, 200, 200, 255), 0, Model3D("./Assets/Models/spider.obj", Position(-0.5, -0.5, -2), Position(0.025, 0.025, 0.025), Position(90, 180, 0))), 3);
    this->_body.push_back(tmp);
    this->_gameData->push_back(tmp);
    tmp = new Cube(Position(this->_head->getPosition().getX() + 15,
                            this->_head->getPosition().getY(), 5),
                            Position(5, 5, 5), Texture("./Assets/Sprites/snake_body.png", Color(200, 200, 200, 255), 0, Model3D("./Assets/Models/spider.obj", Position(-0.5, -0.5, -2), Position(0.025, 0.025, 0.025), Position(90, 180, 0))), 3);
    this->_body.push_back(tmp);
    this->_gameData->push_back(tmp);
    this->_isAlive = true;
    this->_frameToSkip = 0;
    this->_score = 0;
    this->_eatSound = new Audio("./Assets/Sounds/snake_eat.wav");
    this->_deathSound = new Audio("./Assets/Sounds/snake_death.wav");
    this->initCamAround(this->_head->getPosition(), this->_nextDirection);
}

SnakeBody::~SnakeBody() {
    delete _camera;
    delete _head;
    delete _apple;
    delete _eatSound;
    delete _deathSound;
}

void SnakeBody::initCamAround(Position const &orbit, int direction) {
    switch (direction) {
        case 0:
            this->_camera->setPositionX(orbit.getX() + 25);
            this->_camera->setPositionY(orbit.getY());
            this->_camera->setIncX(270);
            break;
        case 1:
            this->_camera->setPositionY(orbit.getY() + 25);
            this->_camera->setPositionX(orbit.getX());
            this->_camera->setIncX(180);
            break;
        case 2:
            this->_camera->setPositionX(orbit.getX() - 25);
            this->_camera->setPositionY(orbit.getY());
            this->_camera->setIncX(90);
            break;
        case 3:
            this->_camera->setPositionY(orbit.getY() - 25);
            this->_camera->setPositionX(orbit.getX());
            this->_camera->setIncX(0);
            break;
    }
}

float SnakeBody::clampToDegree(float f) const {
    if (f < 0)
        f += 360;
    if (f > 360)
        f -= 360;
    return f;
}

void SnakeBody::rotateCamAround(Position const &orbit, int direction) {
    float to_reach = 0;
    switch (direction) {
        case 0:
            to_reach = 270;
            break;
        case 1:
            to_reach = 180;
            break;
        case 2:
            to_reach = 90;
            break;
        case 3:
            to_reach = 0;
            break;
    }
    float diff = to_reach - this->_camera->getIncX();
    float toAdd   = 0.05 * (diff < -180 ? diff + 360 : diff);
    float newAngle = 0;
    if (toAdd > 0.01 || toAdd < -0.01)
        newAngle = this->_camera->getIncX() + toAdd;
    else
        newAngle = (int)this->_camera->getIncX();
    Position to_reach_pos = this->_oldPos + ((orbit - this->_oldPos) / 10) * _frameToSkip;
    float eyeX  = to_reach_pos.getX() - 35 * sin(DTR(newAngle));
    float eyeY  = to_reach_pos.getY() - 35 * cos(DTR(newAngle));
    this->_camera->setPosition(Position(eyeX, eyeY, this->_camera->getPosition().getZ()));
    this->_camera->setIncX(clampToDegree(newAngle));
}

void SnakeBody::Play() {
    this->rotateCamAround(this->_head->getPosition(), this->_direction);
    this->_frameToSkip++;
    this->removeExtraData();
    if (!this->_isAlive) {
        if (this->_karcadeMode == false && this->_frameToSkip % 3 == 0 && this->_body.size() > 0) {
            Cube *tmp = this->_body[this->_body.size() - 1];
            this->_body.pop_back();
            for (size_t i = 0; i < this->_gameData->size(); i++) {
                if (tmp == this->_gameData[0][i]) {
                    this->_gameData->erase(this->_gameData->begin() + i);
                }
            }
        }
        return;
    }
    if (this->_karcadeMode == false) {
        if ((this->_frameToSkip + 1) % 10 != 0)
            return;
    }
    this->_prevDirection = this->_direction;
    this->_direction = this->_nextDirection;
    if (this->moveHead()) {
        this->_butterflyData.push_back(this->_deathSound);
        this->_gameData->push_back(this->_deathSound);
        return;
    }
    if (this->_head->getPosition() == this->_apple->getPosition()) {
        this->addBodyBlock();
    }
    this->_frameToSkip = 0;
}

void SnakeBody::removeExtraData() {
    for (auto const & toDelete: this->_butterflyData) {
        for (size_t i = 0; i < this->_gameData->size(); i++) {
            if (toDelete == this->_gameData[0][i]) {
                this->_gameData->erase(this->_gameData->begin() + i);
            }
        }
    }
    this->_butterflyData.clear();
}

void SnakeBody::moveBody(Position const & oldHeadPos, int oldHeadRot) {
    if (this->_body.size() > 0) {
        for(int i = this->_body.size() - 1; i > 0; i--) {
            this->_body[i]->setPositionX(this->_body[i - 1]->getPosition().getX());
            this->_body[i]->setPositionY(this->_body[i - 1]->getPosition().getY());
            this->_body[i]->setRotation(this->_body[i - 1]->getTexture().getRotation());
        }
        this->_body[0]->setPositionX(oldHeadPos.getX());
        this->_body[0]->setPositionY(oldHeadPos.getY());
        this->_body[0]->setRotation(oldHeadRot);
    }
}

int SnakeBody::moveHead() {
    this->_oldPos = this->_head->getPosition();
    int oldHeadPosX = this->_head->getPosition().getX();
    int oldHeadPosY = this->_head->getPosition().getY();
    switch (this->_direction) {
        case 0:
            this->_head->setPositionX(this->_head->getPosition().getX() - 5);
            this->_head->setRotation(180);
            break;
        case 1:
            this->_head->setPositionY(this->_head->getPosition().getY() - 5);
            this->_head->setRotation(270);
            break;
        case 2:
            this->_head->setPositionX(this->_head->getPosition().getX() + 5);
            this->_head->setRotation(0);
            break;
        case 3:
            this->_head->setPositionY(this->_head->getPosition().getY() + 5);
            this->_head->setRotation(90);
            break;
    }
    for (auto const & block: this->_body) {
        if (this->_head->getPosition() == block->getPosition()) {
            this->_isAlive = 0;
            this->_head->setPosition(Position(oldHeadPosX, oldHeadPosY, 5));
            return (1);
        }
    }
    if (this->_head->getPosition().getX() < 0 || this->_head->getPosition().getX() >= 100 ||
        this->_head->getPosition().getY() < 0 || this->_head->getPosition().getY() >= 100) {
            this->_isAlive = 0;
            this->_head->setPosition(Position(oldHeadPosX, oldHeadPosY, 5));
            return (1);
        }
    this->moveBody(Position(oldHeadPosX, oldHeadPosY, 5), this->_head->getTexture().getRotation());
    return (0);
}

void SnakeBody::addBodyBlock() {
    Cube *tmp = NULL;
    AVisual *lastBlock = this->_body.size() == 0 ? dynamic_cast<AVisual *>(this->_head) : dynamic_cast<AVisual *>(this->_body[this->_body.size() - 1]);
    switch (this->_direction) {
        case 0:
            tmp = new Cube(Position(lastBlock->getPosition().getX() + 5,
                                     lastBlock->getPosition().getY(), 5),
                                     Position(5, 5, 5), Texture("./Assets/Sprites/snake_body.png", Color(200, 200, 200, 255), 3, Model3D("./Assets/Models/spider.obj", Position(-0.5, -0.5, -2), Position(0.025, 0.025, 0.025), Position(90, 180, 0))));
            break;
        case 1:
            tmp = new Cube(Position(lastBlock->getPosition().getX(),
                                    lastBlock->getPosition().getY() + 5, 5),
                                    Position(5, 5, 5), Texture("./Assets/Sprites/snake_body.png", Color(200, 200, 200, 255), 3, Model3D("./Assets/Models/spider.obj", Position(-0.5, -0.5, -2), Position(0.025, 0.025, 0.025), Position(90, 180, 0))));
            break;
        case 2:
            tmp = new Cube(Position(lastBlock->getPosition().getX() - 5,
                                     lastBlock->getPosition().getY(), 5),
                                     Position(5, 5, 5), Texture("./Assets/Sprites/snake_body.png", Color(200, 200, 200, 255), 3, Model3D("./Assets/Models/spider.obj", Position(-0.5, -0.5, -2), Position(0.025, 0.025, 0.025), Position(90, 180, 0))));
            break;
        case 3:
            tmp = new Cube(Position(lastBlock->getPosition().getX(),
                                     lastBlock->getPosition().getY() - 5, 5),
                                     Position(5, 5, 5), Texture("./Assets/Sprites/snake_body.png", Color(200, 200, 200, 255), 3, Model3D("./Assets/Models/spider.obj", Position(-0.5, -0.5, -2), Position(0.025, 0.025, 0.025), Position(90, 180, 0))));
            break;
    }
    this->_body.push_back(tmp);
    this->_gameData->push_back(tmp);
    this->_apple->setPosition(getNewApplePosition());
    this->_score ++;
    this->_butterflyData.push_back(this->_eatSound);
    this->_gameData->push_back(this->_eatSound);
}

Position const SnakeBody::getNewApplePosition() const {
    int appleX = (this->_randGenerator.getRand() % 19) * 5;
    int appleY = (this->_randGenerator.getRand() % 19) * 5;
    for (auto const &block: this->_body) {
        if (block->getPosition().getX() == appleX && block->getPosition().getY() == appleY) {
            return (getNewApplePosition());
        }
    }
    return Position(appleX, appleY, 5);
}

Position const &SnakeBody::getHeadPosition() const {
    return this->_head->getPosition();
}

unsigned int SnakeBody::getScore() const {
    return this->_score;
}

bool SnakeBody::isAlive() const {
    return this->_isAlive;
}

//0: LEFT,   1: UP,   2: RIGHT,   3: DOWN
void SnakeBody::goLeft() {
    if (this->_karcadeMode) {
        if (this->_direction != 2)
            this->_nextDirection = 0;
    } else {
        this->_nextDirection = this->_direction - 1;
        if (this->_nextDirection < 0)
            this->_nextDirection = 3;
    }
}

void SnakeBody::goRight() {
    if (this->_karcadeMode) {
        if (this->_direction != 0)
            this->_nextDirection = 2;
    } else {
        this->_nextDirection = this->_direction + 1;
        if (this->_nextDirection > 3)
            this->_nextDirection = 0;
    }
}

void SnakeBody::goDown() {
    if (this->_karcadeMode) {
        if (this->_direction != 1)
            this->_nextDirection = 3;
    }
}

void SnakeBody::goUp() {
    if (this->_karcadeMode) {
        if (this->_direction != 3)
            this->_nextDirection = 1;
    }
}

arcade::TileType SnakeBody::findBlockAt(int x, int y) const {
    if (this->_apple->getPosition().getX()/5 == x &&
        this->_apple->getPosition().getY()/5 == y)
        return arcade::TileType::POWERUP;
    for (auto const &block: this->_body) {
        if (block->getPosition().getX()/5 == x &&
            block->getPosition().getY()/5 == y) {
            return arcade::TileType::EVIL_DUDE;
        }
    }
    return arcade::TileType::EMPTY;
}
