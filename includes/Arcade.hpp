//
// arcade.hpp for  in /home/sousa_v/rendu/cpp_arcade
//
// Made by Victor Sousa
// Login   <sousa_v@epitech.net>
//
// Started on  Mon Mar 13 22:41:21 2017 Victor Sousa
// Last update Sun Apr  9 01:23:38 2017 Gaëtan Léandre
//

#ifndef ARCADE_HPP_
#define ARCADE_HPP_

#include <vector>
#include <thread>
#include <algorithm>

#include "IArcadeBridge.hpp"
#include "ScoreManager.hpp"
#include "IGraph.hpp"
#include "ExternLib.hpp"
#include "DirectoryManager.hpp"
#include "Menu.hpp"

typedef IGame *(*game_ptr)();
typedef IGraph *(*lib_ptr)();

class Arcade: public IArcadeBridge {

public:
    enum Running
    {
        MENU,
        RUNNING,
        EXIT
    };

    Arcade ();
    ~Arcade ();
    Arcade &operator=(const Arcade &obj);

    void Setup();
    void Start(std::string const &startingLib);
    void mainLoop();

    void toggleRunning();

    void prevGraph();
    void nextGraph();

    void prevGame();
    void nextGame();

    void goUp() const;
    void goDown() const;
    void goLeft() const;
    void goRight() const;
    void goForward() const;
    void shoot() const;
    void pressEchap();
    void pressEight();
    void pressNine();
    void InitCurrentGame(int index);
    std::string &getSetName();

private:
    Arcade(const Arcade &obj);

    void FillGameVector();
    void FillGraphVector();
    void transfertData() const;
    void transfertLoad() const;

    Running _isRunning;
    int _frameRate;

    IGraph* _currentGraph;
    int _currentGraphIndex;
    IGame* _currentGame;
    int _currentGameIndex;
    std::vector<lib_ptr> _libGraph;
    std::vector<std::string> _libGraphName;
    std::vector<game_ptr> _libGame;
    std::vector<ScoreManager *> _scoreVector;
    std::string _name;
    Menu *_menu;
    std::vector<void *> _hanldeList;
};

#else

class Arcade;

#endif /*ARCADE_HPP_*/
