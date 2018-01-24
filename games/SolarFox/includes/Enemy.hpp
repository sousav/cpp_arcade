/*
** Enemy.hpp for Shared in /Users/gmblucas/Desktop/Shared/cpp_arcade/games/SolarFox/includes
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Wed Mar 29 14:42:57 2017 Lucas Gambini
** Last update Tue Apr 04 13:49:25 2017 Lucas Gambini
*/

#ifndef ENEMY_HPP_
#define ENEMY_HPP_

#include <vector>
#include <iostream>
#include "SolarFox.hpp"
#include "Cube.hpp"
#include "Position.hpp"
#include "Missile.hpp"
#include "SpaceShip.hpp"
#include "RandomWrapper.hpp"

class Enemy {

public:
    Enemy (Position startingPos, char direction, std::vector <AData *> *data, SpaceShip *ship, int difficulty);
    virtual ~Enemy ();

    void Play();
    void shoot();

    void setInactive();

    void moveEnemy();
    void moveMissile();

    bool isActive() const;
    Cube *getCube() const;

private:

    double _speed;
    double _inactiveCount;
    bool _isActive;
    char _direction;
    char _shootDirection;
    int _difficulty;
    double _canShoot;

    Cube *_enemy;
    std::vector<Missile*> _missileV;
    std::vector <AData *> *_gameData;
    SpaceShip *_ship;
    RandomWrapper rd;
};

#else

class Enemy;

#endif /* !ENEMY_HPP_ */
