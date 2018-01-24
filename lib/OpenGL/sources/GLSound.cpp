//
// GLSound.cpp for  in /Users/vicostudio/Documents/Shared Folder/TEK2/CPP/cpp_arcade/lib/OpenGL/sources/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Mon Mar 27 23:08:42 2017 Sousa Victor
// Last update Sun Apr  9 21:34:02 2017 Sousa Victor
//

#include "GLSound.hpp"

std::map<std::string, sf::SoundBuffer *> GLSound::_soundBufferMap;
std::vector<sf::Sound *> GLSound::_soundList;

GLSound::GLSound(Audio const &audio): _audio(audio) {

}

GLSound::~GLSound() {

}

void GLSound::clean() {
    for(std::vector<sf::Sound *>::iterator it=GLSound::_soundList.begin() ; it < GLSound::_soundList.end(); it++ ) {
        (*it)->stop();
        delete (*it);
    }
    for(std::map<std::string, sf::SoundBuffer *>::iterator it=GLSound::_soundBufferMap.begin() ; it != GLSound::_soundBufferMap.end(); it++ ) {
        delete (it->second);
    }
}

GLSound &GLSound::operator=(const GLSound &obj) {
    this->_audio = obj._audio;
    return *this;
}

GLSound::GLSound(GLSound const &obj): _audio(obj._audio) {

}


void GLSound::play() const {
    std::map<std::string, sf::SoundBuffer *>::iterator it = this->_soundBufferMap.find(this->_audio.getAudio());
    if (it != this->_soundBufferMap.end()) {
        sf::Sound *sound = new sf::Sound();
        sound->setBuffer(*it->second);
        sound->setVolume(this->_audio.getIntensity());
        GLSound::_soundList.push_back(sound);
        sound->play();
    } else {
        std::cout << "loading: " << this->_audio.getAudio() << std::endl;
        sf::SoundBuffer *buffer = new sf::SoundBuffer();
        buffer->loadFromFile(this->_audio.getAudio());
        this->_soundBufferMap[this->_audio.getAudio()] = buffer;
        sf::Sound *sound = new sf::Sound();
        sound->setBuffer(*buffer);
        GLSound::_soundList.push_back(sound);
        sound->play();
    }
}
