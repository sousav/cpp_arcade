//
// SolarFox.cpp for  in /home/gambin_l/Shared/cpp_arcade/Game/SolarFox
//
// Made by lucas gambini
// Login   <gambin_l@epitech.net>
//
// Started on  Thu Mar 16 18:30:04 2017 lucas gambini
// Last update Sun Apr  9 21:01:30 2017 Sousa Victor
//

#include "SolarFox.hpp"

std::chrono::time_point<std::chrono::system_clock> SolarFox::_oldTime;
double SolarFox::GlobalSpeed = 30;
bool SolarFox::karcadeMode = false;
SolarFox::SolarFox() {
    this->_gameName = std::string("SolarFox! :D");
    this->_frameRate = 500;
    _difficulty = 3;
    _musicStarted = false;
    _scoreManager = NULL;
    _isScoreUpdated = false;
}

SolarFox::~SolarFox () {
    delete _background;
    delete _ship;
    delete _scoreText;
    delete _bestScoreText;
    delete _endgameText;
    delete _audio;
    delete _camera;
}

void SolarFox::InitGame() {


    if (SolarFox::karcadeMode == true)
        SolarFox::GlobalSpeed = 1;
    else
        SolarFox::GlobalSpeed = 30;

    this->_background = new Cube(Position(5, 5, -5), Position(90, 90, 1), Texture("./Assets/Sprites/SolarFoxBack.jpg", Color(0, 0, 0, 255)), 1);
    this->_data.push_back(this->_background);

    for (size_t i = 0; i < 100; i += 5) {
        _data.push_back(new Cube(Position(i, 95, -6), Position(5, 5, 1), Texture("", Color(0, 0, 0, 255)), 1, 14));
        _data.push_back(new Cube(Position(i, 0, -6), Position(5, 5, 1), Texture("", Color(0, 0, 0, 255)), 1, 14));
    }

    for (size_t i = 0; i < 95; i += 5) {
        _data.push_back(new Cube(Position(0, i, -6), Position(5, 5, 1), Texture("", Color(0, 0, 0, 255)), 1, 14));
        _data.push_back(new Cube(Position(95, i, -6), Position(5, 5, 1), Texture("", Color(0, 0, 0, 255)), 1, 14));
    }

    SolarFox::updateElaspedTime();

    _scoreText = new Text(std::string("Score: 0"), 20, Position (1, 1), 99);
    _scoreText->setTexture(Texture(Color(255, 255, 255, 255)));
    _scoreText->setAlign(Text::Align::LEFT);
    if (_scoreManager)
        _bestScoreText = new Text(std::string("Best Score: ") + std::to_string(_scoreManager->getBestScore()), 20, Position (1, 1), 99);
    else
        _bestScoreText = new Text(std::string("Best Score: 0"), 20, Position (1, 1), 99);
    _bestScoreText->setTexture(Texture(Color(255, 255, 255, 255)));
    _bestScoreText->setAlign(Text::Align::RIGHT);
    _endgameText = new Text(std::string(""), 50, Position (50, 50), 99);
    _endgameText->setTexture(Texture(Color(255, 255, 255, 255)));
    _endgameText->setAlign(Text::Align::CENTER);

    _data.push_back(_endgameText);
    _data.push_back(_scoreText);
    _data.push_back(_bestScoreText);

    //Génération de la map

    //BLOC HAUT
    _map.push_back(new Cube(Position(47.5, 17.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(42.5, 22.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(47.5, 22.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(52.5, 22.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(37.5, 27.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(42.5, 27.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(47.5, 27.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(52.5, 27.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(57.5, 27.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(32.5, 32.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(37.5, 32.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(42.5, 32.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(47.5, 32.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(52.5, 32.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(57.5, 32.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(62.5, 32.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));


    // BLOC BAS
    _map.push_back(new Cube(Position(47.5, 77.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(42.5, 72.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(47.5, 72.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(52.5, 72.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(37.5, 67.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(42.5, 67.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(47.5, 67.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(52.5, 67.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(57.5, 67.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(32.5, 62.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(37.5, 62.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(42.5, 62.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(47.5, 62.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(52.5, 62.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(57.5, 62.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(62.5, 62.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));


    // BLOC DROIT
    _map.push_back(new Cube(Position(77.5, 47.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(72.5, 42.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(72.5, 47.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(72.5, 52.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(67.5, 37.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(67.5, 42.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(67.5, 47.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(67.5, 52.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(67.5, 57.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(62.5, 37.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(62.5, 42.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(62.5, 47.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(62.5, 52.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(62.5, 57.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));


    //BLOC GAUCHE
    _map.push_back(new Cube(Position(17.5, 47.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(22.5, 42.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(22.5, 47.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(22.5, 52.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(27.5, 37.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(27.5, 42.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(27.5, 47.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(27.5, 52.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(27.5, 57.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(32.5, 37.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(32.5, 42.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(32.5, 47.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(32.5, 52.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));
    _map.push_back(new Cube(Position(32.5, 57.5), Position(5, 5, 5), Texture("./Assets/Sprites/coin_01.png", Color(255, 255, 0, 255), 0, Model3D("./Assets/Models/TyveKrone.obj", Position(0, 0, 0), Position(1.75, 1.75, 1.75), Position(0, 0, this->_randGenerator.getRand() % 360))), 2, 42));


    for(std::vector<AData*>::iterator it = _map.begin(); it != _map.end() ; *it++) {
        _data.push_back(*it);
    }

    _ship = new SpaceShip(Position(47.5, 47.5), &_data, &_map);

    _enemyV.push_back(new Enemy(Position(95, 95), 0, &_data, _ship, _difficulty));
    _enemyV.push_back(new Enemy(Position(0, 95), 1, &_data, _ship, _difficulty));
    _enemyV.push_back(new Enemy(Position(0, 0), 2, &_data, _ship, _difficulty));
    _enemyV.push_back(new Enemy(Position(95, 0), 3, &_data, _ship, _difficulty));

    _ship->giveEnemyVector(&_enemyV);

    _camera = new Camera(Position(50, 80, 60), 180, -15);
    _data.push_back(_camera);

    _audio = new Audio("./Assets/Sounds/SolarFoxLoop.wav");
    _data.push_back(_audio);

    _spriteList.push_back("./Assets/Sprites/SolarFoxBack.jpg");
    _musicList.push_back("./Assets/Sounds/SolarFoxLoop.wav");
    _spriteList.push_back("./Assets/Sprites/coin_01.png");
    _spriteList.push_back("./Assets/Sprites/fox_ship2.png");
    _spriteList.push_back("./Assets/Sprites/fox_ship1.png");
}

void SolarFox::setKarcadeMode(bool mode) {
    SolarFox::karcadeMode = mode;
}

std::string const & SolarFox::getGameName() const {
    return _gameName;
}

int SolarFox::getFrameRatePerSecond() const {
    return _frameRate;
}

std::vector <AData *> const & SolarFox::getData() const {
    return _data;
}

std::vector <std::string> const & SolarFox::getSprite() const {
    return _spriteList;
}
std::vector <std::string> const & SolarFox::getMusic() const {
    return this->_musicList;
}
std::vector <std::string> const & SolarFox::getModel3D() const {
    return this->_modelList;
}

void SolarFox::setScoreManager(ScoreManager *scoreManager) {
    _scoreManager = scoreManager;
}

void SolarFox::updateNewScore() const {
    if (_scoreManager)
        _scoreManager->pushNewScore(_ship->getScore());
}

void SolarFox::play() {
    _ship->Play();
    _scoreText->setText(std::string("Score: ") + std::to_string(_ship->getScore()));
    if (_ship->isAlive() == false)
    {
        if (_isScoreUpdated == false)
        {
            _isScoreUpdated = true;
            updateNewScore();
        }
        _scoreText->setPosition(Position(50, 55));
        _scoreText->setAlign(Text::Align::CENTER);
        _endgameText->setText(std::string("GameOver!!"));
    }
    if (_ship->getScore() == 1800)
    {
        if (_isScoreUpdated == false)
        {
            _isScoreUpdated = true;
            updateNewScore();
        }
        _scoreText->setPosition(Position(50, 55));
        _scoreText->setAlign(Text::Align::CENTER);
        _endgameText->setText(std::string("You Win !!"));
    }
    if (std::find(_data.begin(), _data.end(), _audio) != _data.end() && _musicStarted == true)
        _data.erase(std::find(_data.begin(), _data.end(), _audio));
    for(std::vector<Enemy*>::iterator it = _enemyV.begin(); it != _enemyV.end() ; *it++) {
        (*it)->Play();
    }
    for (auto const &coinD : _map) {
        Cube *coin = dynamic_cast<Cube *>(coinD);
        coin->setRotation(coin->getTexture().getRotation() + 1);
    }
    _musicStarted = _musicStarted == false ? true : false;
    SolarFox::updateElaspedTime();
}

void SolarFox::getMap() {
    arcade::GetMap *map;

	map = reinterpret_cast<struct arcade::GetMap*>(new char[sizeof(struct arcade::GetMap) + sizeof(arcade::TileType) * 20 * 20]);

    map->type = arcade::CommandType::GET_MAP;
    map->width = 20;
    map->height = 20;

    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 20; x++) {
            map->tile[x + y * 20] = findBlockAt(x * 5, y * 5);
        }
    }

    write(1, map, sizeof(struct arcade::GetMap) + sizeof(arcade::TileType) * 20 * 20);
    delete map;
}

arcade::TileType SolarFox::findBlockAt(int x, int y) {
    arcade::TileType tmp = arcade::TileType::EMPTY;
    int _x;
    int _y;

    for(std::vector<AData*>::iterator it = _data.begin(); it != _data.end() ; *it++) {
        _x = (*it)->getPosition().getX() - ((int)(*it)->getPosition().getX() % 5);
        _y = (*it)->getPosition().getY() - ((int)(*it)->getPosition().getY() % 5);
        if ( x == _x && y == _y ) {
            if ( (*it)->getShape() == DataType::Cube ) {
                if ( ((Cube*)(*it))->getId() == 14 )
                    tmp = arcade::TileType::BLOCK;
                else if ( ((Cube*)(*it))->getId() == 42 )
                    tmp = arcade::TileType::BLOCK;
                else if ( ((Cube*)(*it))->getId() == 69 )
                    tmp = arcade::TileType::MY_SHOOT;
                else if ( ((Cube*)(*it))->getId() == 70 )
                    tmp = arcade::TileType::EVIL_SHOOT;
                else if ( ((Cube*)(*it))->getId() == 1337 )
                    tmp = arcade::TileType::EVIL_DUDE;
                else
                    tmp = arcade::TileType::EMPTY;
            }
        }
    }
    return tmp;
}

void SolarFox::whereIAm() {
    arcade::WhereAmI *where;
    arcade::Position pos;

    where = reinterpret_cast<struct arcade::WhereAmI*>(new char[sizeof(struct arcade::WhereAmI) + sizeof(arcade::Position)]);

    where->type = arcade::CommandType::WHERE_AM_I;
    where->lenght = 1;
    pos.x = _ship->getCube()->getPosition().getX() / 20 + (int)_ship->getCube()->getPosition().getX() % 20;
    pos.y = _ship->getCube()->getPosition().getY() / 20 + (int)_ship->getCube()->getPosition().getY() % 20;
    where->position[0] = pos;

    write(1, where, sizeof(struct arcade::WhereAmI) + sizeof(arcade::Position));
    delete where;
}

void SolarFox::goUp() {
    _ship->goUp();
}

void SolarFox::goDown() {
    _ship->goDown();
}

void SolarFox::goLeft() {
    _ship->goLeft();
}

void SolarFox::goRight() {
    _ship->goRight();
}

void SolarFox::goForward() {
    _ship->goForward();
}

void SolarFox::shoot() {
    _ship->shoot();
}

void SolarFox::updateElaspedTime() {
    SolarFox::_oldTime = std::chrono::system_clock::now();
}

double SolarFox::getElaspedTime() {
    if (SolarFox::karcadeMode == true)
        return 1;
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = now - SolarFox::_oldTime;
    return elapsed.count();
}

extern "C" {

    IGame *Create()
    {
        return new SolarFox();
    }

    void switch1(SolarFox &slFox, arcade::CommandType const input)
    {
        switch ((uint16_t)input)
        {
            case 0:
                slFox.whereIAm();
                break;
            case 1:
                slFox.getMap();
                break;
            case 2:
                slFox.goUp();
                break;
            case 3:
                slFox.goDown();
                break;
            default:
                break;
        }
    }

    void switch2(SolarFox &slFox, arcade::CommandType const input)
    {
        switch ((uint16_t)input)
        {
            case 4:
                slFox.goLeft();
                break;
            case 5:
                slFox.goRight();
                break;
            case 6:
                slFox.goForward();
                break;
            case 7:
                slFox.shoot();
                break;
            case 9:
                slFox.play();
                break;
            default:
                break;
        }
    }

    void Play()
    {
        SolarFox slFox;
        arcade::CommandType input;

        slFox.setKarcadeMode(true);
        slFox.InitGame();
        while (read(0, &input, sizeof(arcade::CommandType)))
        {
            switch1(slFox, input);
            switch2(slFox, input);
        }
    }
}
