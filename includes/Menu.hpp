//
// Menu.hpp for menu in /Users/leandr_g/Documents/Shared folder/cpp_arcade/includes/
//
// Made by Gaëtan Léandre
// Login   <leandr_g@epitech.eu>
//
// Started on  Wed Apr  5 16:53:53 2017 Gaëtan Léandre
// Last update Sun Apr  9 01:06:28 2017 Gaëtan Léandre
//

#ifndef MENU_HPP_
#define MENU_HPP_

#include <string>
#include "Arcade.hpp"
#include "IGame.hpp"
#include "Position.hpp"
#include "Cube.hpp"
#include "Text.hpp"
#include "Sphere.hpp"

typedef IGame *(*game_ptr)();

class Menu : public IGame
{
public:
    enum Choice
    {
        GAME,
        HIGHSCORE,
        NAME
    };

    virtual ~Menu();
    Menu();
    virtual void InitGame();
    virtual std::string const &getGameName() const;
    virtual int getFrameRatePerSecond() const;
    virtual std::vector <AData *> const &getData() const;

    virtual std::vector <std::string> const & getSprite() const;
    virtual std::vector <std::string> const & getMusic() const;
    virtual std::vector <std::string> const & getModel3D() const;

    virtual void setScoreManager(ScoreManager *scoreManager);
    virtual void updateNewScore() const;

    virtual void play();
    virtual void getMap();
    virtual void whereIAm();

    virtual void goUp();
    virtual void goDown();
    virtual void goLeft();
    virtual void goRight();
    virtual void goForward();
    virtual void shoot();

    void setGames(std::vector <std::string>  const &file);
    void setScoreVector(std::vector<ScoreManager *> const &scoreVector);
    void setArcade(Arcade *arc);

private:
    std::vector <AData *> _dataGame;
    std::vector <AData *> _dataHigh;
    std::vector <AData *> _dataName;

    std::string _name;
    Cube *_background;
    Text *_title;
    Sphere *_earth;
    std::vector <Text *> _games;
    std::vector <Text *> _highscore;
    std::vector <Text *> _ctn;
    std::vector <Text *> _nameVec;
    std::vector <std::string> _spriteList;
    std::vector <std::string> _musicList;
    std::vector <std::string> _modelList;
    std::vector<ScoreManager *> _scoreVector;
    size_t _pos;
    size_t _ctnPos;
    size_t _posName;
    Choice _choice;
    Arcade *_arc;
};

#else

class Menu;

#endif /* !MENU_HPP_ */
