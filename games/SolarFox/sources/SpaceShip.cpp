/*
** SpaceShip.cpp for Shared in /Users/gmblucas/Desktop/Shared/cpp_arcade/games/SolarFox/sources
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Fri Mar 24 02:10:16 2017 Lucas Gambini
** Last update Sun Apr  9 00:32:02 2017 Sousa Victor
*/

#include "SpaceShip.hpp"

SpaceShip::SpaceShip(Position startingPos, std::vector <AData *> *data, std::vector <AData *> *map)
{
    _gameData = data;
    _map = map;
    _ship = new Cube(startingPos, Position(5, 5, 5), Texture("./Assets/Sprites/fox_ship2.png", Color(255, 0, 0, 255), 0, Model3D("./Assets/Models/LPSpaceShip.obj", Position(0, 0, 5), Position(2, 2, 2), Position(90, 0, 0))), 3, 22);
    _gameData->push_back(_ship);
    _isAlive = true;
    _direction = -1;
    _nextDirection = -1;
    _speed = SolarFox::GlobalSpeed;
    _delta = 0;
    _score = 0;
    _isBoosted = false;
    _boostCount = 0;
}

SpaceShip::~SpaceShip()
{
    delete _ship;
}

void SpaceShip::Play()
{
    if (!_isAlive)
        return;
    _direction = _nextDirection;
    moveShip();
    moveMissiles();
    if (_isBoosted)
    {
        _boostCount += SolarFox::getElaspedTime();
        if (_boostCount >= 0.3) {
            _isBoosted = false;
            _speed = SolarFox::GlobalSpeed;
            _boostCount = 0;
        }
    }
}

char SpaceShip::getDirection() const {
    return this->_direction;
}

void SpaceShip::moveMissiles()
{
    for(std::vector<Missile*>::iterator it = _missileV.begin(); it != _missileV.end(); ++it) {

        (*it)->move();

        for(std::vector<AData*>::iterator itMap = _map->begin(); itMap != _map->end(); ++itMap) {
            if ((*itMap)->getShape() != DataType::Cube)
                continue;
            if ((*(*it)->getCube()) == (*(Cube*)(*itMap))) {
                _score += 30;
                if (std::find(_gameData->begin(), _gameData->end(), *itMap) != _gameData->end())
                    _gameData->erase(std::find(_gameData->begin(), _gameData->end(), *itMap));
                _map->erase(itMap);
                delete *it;
                _missileV.erase(it);
                return;
            }
        }

        for(std::vector<Enemy*>::iterator itEn = _enemyV->begin(); itEn != _enemyV->end(); ++itEn) {

            if ((*(*it)->getCube()) == (*(*itEn)->getCube())) {
                (*itEn)->setInactive();
                delete *it;
                _missileV.erase(it);
                return;
            }
        }

        if ((*it)->checkPos() == false)
        {
            delete *it;
            _missileV.erase(it);
            return;
        }
    }
}

//0: LEFT,   1: UP,   2: RIGHT,   3: DOWN
void SpaceShip::moveShip()
{
    if (_isBoosted == true && _speed == SolarFox::GlobalSpeed)
        _speed += 30;
    switch (_direction) {
        case 0:
            _ship->setPositionX(_ship->getPosition().getX() - _speed * SolarFox::getElaspedTime());
            _ship->setRotation(-90);
            break;
        case 1:
            _ship->setPositionY(_ship->getPosition().getY() - _speed * SolarFox::getElaspedTime());
            _ship->setRotation(0);
            break;
        case 2:
            _ship->setPositionX(_ship->getPosition().getX() + _speed * SolarFox::getElaspedTime());
            _ship->setRotation(90);
            break;
        case 3:
            _ship->setPositionY(_ship->getPosition().getY() + _speed * SolarFox::getElaspedTime());
            _ship->setRotation(180);
            break;
    }
    if (_ship->getPosition().getX() <= 5 || _ship->getPosition().getX() >= 90 ||
        _ship->getPosition().getY() <= 5 || _ship->getPosition().getY() >= 90)
        _isAlive = false;
}

int SpaceShip::getScore() const
{
    return _score;
}

bool SpaceShip::isAlive() const
{
    return _isAlive;
}

//0: LEFT,   1: UP,   2: RIGHT,   3: DOWN
void SpaceShip::goLeft() {
    if (_direction != 2)
        _nextDirection = 0;
    if (SolarFox::karcadeMode == true)
        _nextDirection = 0;
}

void SpaceShip::goRight() {
    if (_direction != 0)
        _nextDirection = 2;
    if (SolarFox::karcadeMode == true)
        _nextDirection = 2;
}

void SpaceShip::goDown() {
    if (_direction != 1)
        _nextDirection = 3;
    if (SolarFox::karcadeMode == true)
        _nextDirection = 3;
}

void SpaceShip::goUp() {
    if (_direction != 3)
        _nextDirection = 1;
    if (SolarFox::karcadeMode == true)
        _nextDirection = 1;
}

void SpaceShip::shoot()
{
    if (_isAlive && _direction != -1)
        _missileV.push_back(new Missile(_ship->getPosition(), _direction, _gameData, 1));
}

void SpaceShip::goForward()
{
    _isBoosted = true;
}

Cube *SpaceShip::getCube() const
{
    return _ship;
}

void SpaceShip::killShip()
{
    _isAlive = false;
}

void SpaceShip::giveEnemyVector(std::vector<Enemy*> *vec)
{
    _enemyV = vec;
}
