//
// SolarFox.hpp for  in /home/gambin_l/Shared/cpp_arcade/Game/SolarFox
//
// Made by lucas gambini
// Login   <gambin_l@epitech.net>
//
// Started on  Thu Mar 16 18:30:11 2017 lucas gambini
// Last update Sun Apr  9 01:19:15 2017 Sousa Victor
//

#ifndef SOLARFOX_HPP_
#define SOLARFOX_HPP_

#include "IGame.hpp"
#include "Text.hpp"
#include "SpaceShip.hpp"
#include "Audio.hpp"
#include "Enemy.hpp"
#include "Camera.hpp"
#include "ScoreManager.hpp"
#include "Protocol.hpp"
#include "math.h"
#include <unistd.h>
#include "RandomWrapper.hpp"

# define DTR(angle) ((angle) / 180.0 * M_PI)

class SolarFox : public IGame {

public:
    SolarFox();
    ~SolarFox();

    void InitGame();

    std::string const &getGameName() const;
    int getFrameRatePerSecond() const;
    std::vector <AData *> const &getData() const;

    std::vector <std::string> const & getSprite() const;
    std::vector <std::string> const & getMusic() const;
    std::vector <std::string> const & getModel3D() const;

    void setScoreManager(ScoreManager *scoreManager);

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

public: static bool karcadeMode;
public: static double GlobalSpeed;
public: static void updateElaspedTime();
public: static double getElaspedTime();
private: static std::chrono::time_point<std::chrono::system_clock> _oldTime;
private:
    RandomWrapper _randGenerator;
    std::string _gameName;
    int _frameRate;
    bool _musicStarted;
    int _difficulty;
    bool _isScoreUpdated;
    std::vector <AData *> _data;
    std::vector <std::string> _spriteList;
    std::vector <std::string> _musicList;
    std::vector <std::string> _modelList;
    std::vector<AData*> _map;
    std::vector<Enemy*> _enemyV;
    SpaceShip *_ship;
    Cube *_background;
    Text *_scoreText;
    Text *_bestScoreText;
    Text *_endgameText;
    Camera *_camera;
    Audio *_audio;
    ScoreManager *_scoreManager;

    void updateNewScore() const;
    arcade::TileType findBlockAt(int x, int y);

};


#endif /* !SOLARFOX_HPP_ */
