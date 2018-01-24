//
// GLSound.hpp for  in /Users/vicostudio/Documents/Shared Folder/TEK2/CPP/cpp_arcade/lib/OpenGL/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Mon Mar 27 23:05:51 2017 Sousa Victor
// Last update Sun Apr  9 21:16:55 2017 Sousa Victor
//

#ifndef GLSOUND_HPP_
#define GLSOUND_HPP_

#ifdef __APPLE__
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
#else
# ifdef _WIN32
   #include <windows.h>
# endif
# include <GL/gl.h>
# include <GL/glu.h>
#endif
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <map>

#include "Audio.hpp"
#include "IGLPlayable.hpp"

class GLSound : public IGLPlayable {

public:
    explicit GLSound(Audio const &audio);
    ~GLSound();
    GLSound &operator=(const GLSound &obj);
    GLSound(GLSound const &obj);

    void play() const;
    static void clean();

public: static std::map<std::string, sf::SoundBuffer *> _soundBufferMap;
public: static std::vector<sf::Sound *> _soundList;
private:
    Audio _audio;

};

#endif /*GLSOUND_HPP_*/
