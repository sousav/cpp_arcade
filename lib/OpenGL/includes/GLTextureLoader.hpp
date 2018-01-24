//
// GLTextureLoader.hpp for  in /Users/vicostudio/Documents/Shared Folder/TEK2/CPP/cpp_arcade/lib/OpenGL/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sun Mar 26 01:31:38 2017 Sousa Victor
// Last update Sun Apr  9 21:07:23 2017 Sousa Victor
//

#ifndef GLTEXTURELOADER_HPP_
#define GLTEXTURELOADER_HPP_

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

#include <SDL/SDL_image.h>

#include <iostream>
#include <string>
#include <map>

class GLTextureLoader {

public:
    ~GLTextureLoader();

    static GLuint load(std::string const & filename, bool useMipMap = false);
    static void clean();

private:
    GLTextureLoader();
    static GLuint loadTexture(const char * filename, bool useMipMap);
    static SDL_Surface *flipSurface(SDL_Surface * surface);

    static std::map<std::string, GLuint> _textureMap;

};

#endif /*GLTEXTURELOADER_HPP_*/
