//
// SnakeBody.hpp for  in /home/gambin_l/Shared/cpp_arcade/Game/Snake
//
// Made by lucas gambini
// Login   <gambin_l@epitech.net>
//
// Started on  Thu Mar 16 17:31:56 2017 lucas gambini
// Last update Sat Apr  8 23:08:54 2017 Sousa Victor
//

#ifndef SNAKEBODY_HPP_
#define SNAKEBODY_HPP_

#include <math.h>
#include <iostream>
#include <vector>

#include "Protocol.hpp"
#include "RandomWrapper.hpp"
#include "Cube.hpp"
#include "Sphere.hpp"
#include "Position.hpp"
#include "Audio.hpp"
#include "Camera.hpp"

# define DTR(angle) ((angle) / 180.0 * M_PI)

class SnakeBody {

public:
    SnakeBody(Position const &startingPos, std::vector <AData *> *data, bool mode);
    ~SnakeBody();

    void Play();

    void goLeft();
    void goRight();
    void goDown();
    void goUp();

    unsigned int getScore() const;
    bool isAlive() const;

    Position const &getHeadPosition() const;

    arcade::TileType findBlockAt(int x, int y) const;

private:
    bool _karcadeMode;
    RandomWrapper _randGenerator;
    std::vector <AData *> *_gameData;

    float clampToDegree(float f) const;
    void initCamAround(Position const &orbit, int direction);
    void rotateCamAround(Position const &orbit, int direction);
    void removeExtraData() ;
    void moveBody(Position const & oldHeadPos, int oldHeadRot);
    int moveHead();
    void addBodyBlock();
    Position const getNewApplePosition() const;

    Position _oldPos;
    bool _isAlive;
    unsigned int _score;
    char _frameToSkip;
    char _prevDirection;
    char _direction; //0: LEFT,   1: UP,   2: RIGHT,   3: DOWN
    char _nextDirection;
    Camera *_camera;
    AVisual *_head;
    std::vector<Cube *> _body;
    Cube *_apple;
    Audio *_eatSound;
    Audio *_deathSound;
    std::vector<AData *> _butterflyData;

};

#endif /*SNAKEBODY_HPP_*/
