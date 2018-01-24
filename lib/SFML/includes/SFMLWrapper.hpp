//
// SFMLWrapper.hpp for  in /home/gambin_l/Shared/cpp_arcade/Graphics/SFML
//
// Made by lucas gambini
// Login   <gambin_l@epitech.net>
//
// Started on  Thu Mar 16 17:44:20 2017 lucas gambini
// Last update Sun Apr  9 21:28:35 2017 Gaëtan Léandre
//

#ifndef SFMLWRAPPER_HPP_
#define SFMLWRAPPER_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Exceptions.hpp"
#include "IGraph.hpp"
#include "Sphere.hpp"
#include "Cube.hpp"
#include "Camera.hpp"
#include "Audio.hpp"
#include "Light.hpp"
#include "Text.hpp"

class SFMLWrapper : public IGraph  {

public:
    SFMLWrapper();
    ~SFMLWrapper();

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

    int handleEvent(sf::Event const & event);

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

    unsigned int _width;
    unsigned int _height;
    sf::RenderWindow *_window;
    sf::Font *_font;
    std::map<std::string, sf::Texture *> _spriteMap;
    std::map<std::string, sf::SoundBuffer *> _soundBufferMap;
    std::vector<sf::Sound *> _soundList;

};

#endif /* SFMLWRAPPER_HPP_*/
