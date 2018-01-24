//
// Snake.hpp for  in /home/gambin_l/Shared/cpp_arcade/Game/Snake
//
// Made by lucas gambini
// Login   <gambin_l@epitech.net>
//
// Started on  Thu Mar 16 17:31:56 2017 lucas gambini
// Last update Sun Apr  9 00:56:26 2017 Sousa Victor
//

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include <memory>
#include <unistd.h>

#include "Protocol.hpp"
#include "ScoreManager.hpp"
#include "IGame.hpp"
#include "Position.hpp"
#include "Cube.hpp"
#include "Text.hpp"
#include "Light.hpp"
#include "SnakeBody.hpp"

class Snake : public IGame {

public:
    Snake();
    ~Snake();

    void InitGame();

    std::string const &getGameName() const;
    int getFrameRatePerSecond() const;
    std::vector <AData *> const &getData() const;

    std::vector <std::string> const & getSprite() const;
    std::vector <std::string> const & getMusic() const;
    std::vector <std::string> const & getModel3D() const;

    void setScoreManager(ScoreManager *scoreManager);
    void updateNewScore() const;

    void play();
    void getMap();
    void whereIAm();

    void goUp();
    void goDown();
    void goLeft();
    void goRight();
    void goForward();
    void shoot();

    void setKarcadeMode(bool mode);

private:
    bool _karcadeMode;
    bool _scoreUpdated;
    std::string _gameName;
    int _frameRate;
    std::vector <AData *> _data;
    std::vector <std::string> _spriteList;
    std::vector <std::string> _musicList;
    std::vector <std::string> _modelList;

    std::vector <Light *> _lightList;
    Cube *_background;
    Text *_scoreText;
    Text *_gameoverText;
    SnakeBody *_snake;
    ScoreManager *_scoreManager;
    arcade::TileType findBlockAt(int x, int y) const;
};

#endif /*SNAKE_HPP_*/
