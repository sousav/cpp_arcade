/*
** Missile.cpp for Shared in /Users/gmblucas/Desktop/Shared/cpp_arcade/games/SolarFox/sources
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Fri Mar 24 04:21:37 2017 Lucas Gambini
** Last update Fri Apr  7 23:03:13 2017 Sousa Victor
*/

#include "Missile.hpp"

Missile::Missile(Position startingPos, char direction, std::vector <AData *> *data, char fromPlayer)
{
    int id = fromPlayer == 0 ? 70 : 69;
    _gameData = data;
    _fromPlayer = fromPlayer;
    _startingPos = startingPos;
    if (SolarFox::karcadeMode == false) {
        _startingPos.setX(_startingPos.getX() + 2.5);
        _startingPos.setY(_startingPos.getY() + 2.5);
        if (direction == 0 || direction == 2)
            _missile = new Cube(_startingPos, Position(3, 1, 1), Texture(Color(255, 128, 0, 255)), 2, id);
        else
            _missile = new Cube(_startingPos, Position(1, 3, 1), Texture(Color(255, 128, 0, 255)), 2, id);
    } else {
        if (direction == 0)
        {
            _startingPos.setX(_startingPos.getX() - 5);
            _missile = new Cube(_startingPos, Position(3, 1, 1), Texture(Color(255, 128, 0, 255)), 2, id);
        }
        else if (direction == 1)
        {
            _startingPos.setY(_startingPos.getY() - 5);
            _missile = new Cube(_startingPos, Position(1, 3, 1), Texture(Color(255, 128, 0, 255)), 2, id);
        }
        else if (direction == 2)
        {
            _startingPos.setX(_startingPos.getX() + 5);
            _missile = new Cube(_startingPos, Position(3, 1, 1), Texture(Color(255, 128, 0, 255)), 2, id);
        }
        else if (direction == 3)
        {
            _startingPos.setY(_startingPos.getY() + 5);
            _missile = new Cube(_startingPos, Position(1, 3, 1), Texture(Color(255, 128, 0, 255)), 2, id);
        }
    }
    _gameData->push_back(_missile);
    _direction = direction;
    if (_fromPlayer == 1)
        _speed = SolarFox::GlobalSpeed * 3;
    else
        _speed = SolarFox::GlobalSpeed * 0.5;
    _audio = new Audio("./Assets/Sounds/laser.wav", 100, false);
    _gameData->push_back(_audio);
}

Missile::~Missile()
{
    if (std::find(_gameData->begin(), _gameData->end(), _missile) != _gameData->end())
    {
        delete _missile;
        _gameData->erase(std::find(_gameData->begin(), _gameData->end(), _missile));
    }
}

void Missile::move()
{
    switch (this->_direction) {
        case 0:
            _missile->setPositionX(_missile->getPosition().getX() - _speed * SolarFox::getElaspedTime());
            break;
        case 1:
            _missile->setPositionY(_missile->getPosition().getY() - _speed * SolarFox::getElaspedTime());
            break;
        case 2:
            _missile->setPositionX(_missile->getPosition().getX() + _speed * SolarFox::getElaspedTime());
            break;
        case 3:
            _missile->setPositionY(_missile->getPosition().getY() + _speed * SolarFox::getElaspedTime());
            break;
    }
    killAudio();
    for(std::vector<AData*>::iterator it = _gameData->begin(); it != _gameData->end(); ++it) {
        if ((*it)->getShape() == DataType::Cube && ((Cube*)(*it))->getId() == 69 &&
            (*(Cube*)(*it)) == (*_missile) && (Cube*)(*it) != _missile && _fromPlayer == 1)
        {
            (*it)->setPosition(Position(150, 150, 150));
            _missile->setPosition(Position(150, 150, 150));
        }
    }
}

void Missile::killAudio()
{
    if (_audio)
    {
        if (std::find(_gameData->begin(), _gameData->end(), _audio) != _gameData->end())
        {
            delete _audio;
            _gameData->erase(std::find(_gameData->begin(), _gameData->end(), _audio));
            _audio = NULL;
        }
    }
}

bool Missile::checkPos()
{
    if (_missile->getPosition().getX() < 0 || _missile->getPosition().getX() > 100 ||
        _missile->getPosition().getY() < 0 || _missile->getPosition().getY() > 100)
        return false;
    if (_fromPlayer == 0)
        return true;
    switch (this->_direction) {
        case 2:
            if (_missile->getPosition().getX() - _startingPos.getX() > 30)
                return false;
            break;
        case 3:
            if (_missile->getPosition().getY() - _startingPos.getY() > 30)
                return false;
            break;
        case 0:
            if (_startingPos.getX() - _missile->getPosition().getX() > 30)
                return false;
            break;
        case 1:
            if (_startingPos.getY() - _missile->getPosition().getY() > 20)
                return false;
            break;
        }
    return true;
}

Cube *Missile::getCube() const
{
    return _missile;
}
