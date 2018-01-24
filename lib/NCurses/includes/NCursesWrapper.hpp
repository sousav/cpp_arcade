//
// NcursesWrapper.hpp for  in /home/gambin_l/Shared/cpp_arcade/lib/NCurses
//
// Made by lucas gambini
// Login   <gambin_l@epitech.net>
//
// Started on  Thu Mar 16 18:43:36 2017 lucas gambini
// Last update Sun Apr  9 00:54:01 2017 Gaëtan Léandre
//

#ifndef NCURSES_H_
#define NCURSES_H_

#include <curses.h>
#include <ncurses.h>

#include "IGraph.hpp"
#include "IGraph.hpp"
#include "Sphere.hpp"
#include "Cube.hpp"
#include "Camera.hpp"
#include "Audio.hpp"
#include "Light.hpp"
#include "Text.hpp"


class NCursesWrapper : public IGraph {

public:
    NCursesWrapper();
    ~NCursesWrapper();

    void InitLib();
    std::string const & getLibName() const;
    void giveData(std::vector <AData *> const &data);
    void giveSprite(std::vector <std::string> const &spriteList);
    void giveMusic(std::vector <std::string> const &musicList);
    void giveModel3D(std::vector <std::string> const &modelList);

    void setBridge(IArcadeBridge * bridge);

    void handleData(AData const & data);
    void handleSphere(AData const & data);
    void handleCube(AData const & data);
    void handleCamera(AData const & data);
    void handleLight(AData const & data);
    void handleMusic(AData const & data);
    void handleText(AData const & data);

private:
    std::string _libName;
    IArcadeBridge *_bridge;

    int handleEvent(int event);
    void setColor(Color const &col);
    void toggleRunning() const;
    void prevGraph() const;
    void nextGraph() const;
    void prevGame() const;
    void nextGame() const;
    void goUp() const;
    void goDown() const;
    void goLeft() const;
    void goRight() const;
    void goForward() const;
    void shoot() const;
    void pressEchap() const;
    void pressEight() const;
    void pressNine() const;
    void createColors();
    void drawSquare();

    unsigned int _width;
    unsigned int _height;
};

#endif
