//
// GLCube.hpp for  in /Users/vicostudio/Documents/Shared Folder/TEK2/CPP/cpp_arcade/lib/OpenGL/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sun Mar 26 00:38:01 2017 Sousa Victor
// Last update Sun Apr  9 03:17:56 2017 Sousa Victor
//

#ifndef GLCUBE_HPP_
#define GLCUBE_HPP_

#ifdef __APPLE__
# include <GL/glew.h>
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
#else
# ifdef _WIN32
   #include <windows.h>
# endif
# include <GL/glew.h>
# include <GL/gl.h>
# include <GL/glu.h>
#endif

#include "IGLDrawable.hpp"
#include "GLTextureLoader.hpp"
#include "Cube.hpp"

class GLCube : public IGLDrawable {

public:
    explicit GLCube(Cube const &cube);
    ~GLCube();
    GLCube &operator=(const GLCube &obj);
    GLCube(GLCube const &obj);

    void draw();

private:
    Cube _cube;

};

#endif /*GLCUBE_HPP_*/
