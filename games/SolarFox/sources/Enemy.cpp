/*
** Enemy.cpp for Shared in /Users/gmblucas/Desktop/Shared/cpp_arcade/games/SolarFox/sources
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Wed Mar 29 17:05:08 2017 Lucas Gambini
** Last update Sun Apr 09 19:53:51 2017 Lucas Gambini
*/

#include "Enemy.hpp"

Enemy::Enemy(Position startingPos, char direction, std::vector <AData *> *data, SpaceShip *ship, int difficulty)
{
    int rotation = 0;
    switch (direction) {
        case 0:
            rotation = -90;
            break;
        case 1:
            rotation = 0;
            break;
        case 2:
            rotation = 90;
            break;
        case 3:
            rotation = 180;
            break;
        default:
            rotation = 0;
            break;
    }
    _enemy = new Cube(startingPos, Position(5, 5, 5), Texture("./Assets/Sprites/fox_ship1.png", Color(255, 0, 0, 255), rotation, Model3D("./Assets/Models/SpaceShip.obj", Position(0, 0, 5), Position(1, 1, 1), Position(90, 0, 0))), 2, 1337);
    _direction = direction;
    _shootDirection = direction;
    _gameData = data;
    _ship = ship;
    _speed = SolarFox::GlobalSpeed;
    _isActive = true;
    _difficulty = difficulty;
    _gameData->push_back(_enemy);
    _canShoot = 0;
    _inactiveCount = 0;
}

Enemy::~Enemy()
{
    delete _enemy;
}

void Enemy::Play()
{
    _canShoot += SolarFox::getElaspedTime();
    moveMissile();
    if (_isActive == false)
    {
        _inactiveCount += SolarFox::getElaspedTime();
        if (_inactiveCount >= 7) {
            _isActive = true;
            _inactiveCount = 0;
        }
        else
            return;
    }
    moveEnemy();
    if (rd.getRand() % 1000 < (unsigned int)_difficulty && _canShoot >= 1)
    {
        _canShoot = 0;
        shoot();
    }
}

void Enemy::shoot()
{
    _missileV.push_back(new Missile(_enemy->getPosition(), _shootDirection, _gameData, 0));
}

void Enemy::moveEnemy()
{
    switch (_direction) {
        case 0:

            _enemy->setPositionY(_enemy->getPosition().getY() + _speed * SolarFox::getElaspedTime());
            if (_enemy->getPosition().getY() >= 95)
                _direction = 2;
            break;
        case 1:
            _enemy->setPositionX(_enemy->getPosition().getX() + _speed * SolarFox::getElaspedTime());
            if (_enemy->getPosition().getX() >= 95)
                _direction = 3;
            break;
        case 2:
            _enemy->setPositionY(_enemy->getPosition().getY() - _speed * SolarFox::getElaspedTime());
            if (_enemy->getPosition().getY() <= 0)
                _direction = 0;
            break;
        case 3:
            _enemy->setPositionX(_enemy->getPosition().getX() - _speed * SolarFox::getElaspedTime());
            if (_enemy->getPosition().getX() <= 0)
                _direction = 1;
            break;
    }
}

void Enemy::moveMissile()
{
    for(std::vector<Missile*>::iterator it = _missileV.begin(); it != _missileV.end(); ++it) {
        (*it)->move();
        if ((*(*it)->getCube()) == (*(_ship->getCube())))
        {
            _ship->killShip();
            delete *it;
            _missileV.erase(it);
            break;
        }

        if ((*it)->checkPos() == false)
        {
            delete *it;
            _missileV.erase(it);
            return;
        }
    }
}

bool Enemy::isActive() const
{
    return _isActive;
}

Cube *Enemy::getCube() const
{
    return _enemy;
}

void Enemy::setInactive()
{
    _isActive = false;
}
