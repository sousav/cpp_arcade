/*
** Missile.hpp for Shared in /Users/gmblucas/Desktop/Shared/cpp_arcade/games/SolarFox/includes
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Fri Mar 24 04:20:51 2017 Lucas Gambini
** Last update Tue Apr 04 13:49:21 2017 Lucas Gambini
*/

#ifndef MISSILE_HPP_
#define MISSILE_HPP_

#include <vector>
#include <algorithm>
#include <iostream>
#include "SolarFox.hpp"
#include "Cube.hpp"
#include "Audio.hpp"

class Missile {

public:
    Missile (Position startingPos, char direction, std::vector <AData *> *data, char fromPlayer);
    virtual ~Missile ();

    void move();
    bool checkPos();

    Cube *getCube() const;

private:

    void killAudio();

    Cube *_missile;
    char _direction;
    double _speed;
    Position _startingPos;
    char _fromPlayer;

    Audio *_audio;
    std::vector <AData *> *_gameData;

};

#else

class Missile;

#endif /* !MISSILE_HPP_ */
