/*
** IGame.hpp for Shared in /Users/gmblucas/Desktop/Shared/cpp_arcade/includes
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Tue Mar 14 03:36:06 2017 Lucas Gambini
** Last update	Sun Apr 09 00:34:37 2017 Full Name
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include <vector>
#include <iostream>

#include "ScoreManager.hpp"
#include "AVisual.hpp"

class IGame {

public:
    virtual ~IGame() {};
    virtual void InitGame() = 0;
    virtual std::string const &getGameName() const = 0;
    virtual int getFrameRatePerSecond() const = 0;
    virtual std::vector <AData *> const &getData() const = 0;

    virtual std::vector <std::string> const & getSprite() const = 0;
    virtual std::vector <std::string> const & getMusic() const = 0;
    virtual std::vector <std::string> const & getModel3D() const = 0;

    virtual void setScoreManager(ScoreManager *scoreManager) = 0;
    virtual void updateNewScore() const = 0;

    virtual void play() = 0;
    virtual void getMap() = 0;
    virtual void whereIAm() = 0;

    virtual void goUp() = 0;
    virtual void goDown() = 0;
    virtual void goLeft() = 0;
    virtual void goRight() = 0;
    virtual void goForward() = 0;
    virtual void shoot() = 0;

protected:

};

#else

class IGame;

#endif /* !IGAME_HPP_ */
