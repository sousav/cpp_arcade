/*
** SpaceShip.hpp for Shared in /Users/gmblucas/Desktop/Shared/cpp_arcade/games/SolarFox/includes
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Fri Mar 24 02:10:10 2017 Lucas Gambini
** Last update Sun Apr  9 00:31:30 2017 Sousa Victor
*/

#ifndef SPACESHIP_HPP_
#define SPACESHIP_HPP_

#include <vector>
#include <iostream>
#include <chrono>
#include "Cube.hpp"
#include "Position.hpp"
#include "Missile.hpp"
#include "Enemy.hpp"
#include "Audio.hpp"
#include "Camera.hpp"
#include "Model3D.hpp"

class SpaceShip {

public:
    SpaceShip (Position startingPos, std::vector <AData *> *data, std::vector <AData *> *map);
    virtual ~SpaceShip ();

    void Play();

    void goLeft();
    void goRight();
    void goDown();
    void goUp();
    void shoot();
    void goForward();

    void moveShip();
    void moveMissiles();

    int getScore() const;
    bool isAlive() const;
    Cube *getCube() const;
    char getDirection() const;
    void killShip();
    void giveEnemyVector(std::vector<Enemy*> *vec);

private:
    Cube *_ship;
    bool _isAlive;
    char _direction;
    char _nextDirection;
    bool _isBoosted;
    double _boostCount;

    std::vector<Enemy*> *_enemyV;
    std::vector<Missile*> _missileV;

    double _speed;
    double _delta;

    std::vector <AData *> *_gameData;
    std::vector <AData *> *_map;

    int _score;
};

#else

class SpaceShip;

#endif /* !SPACESHIP_HPP_ */
