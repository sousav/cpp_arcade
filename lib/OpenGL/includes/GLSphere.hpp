//
// GLSphere.hpp for  in /Users/vicostudio/Documents/Shared Folder/TEK2/CPP/cpp_arcade/lib/OpenGL/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Thu Mar 30 23:46:22 2017 Sousa Victor
// Last update Sun Apr  9 03:24:26 2017 Sousa Victor
//

#ifndef GLSPHERE_HPP_
#define GLSPHERE_HPP_

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

#include <math.h>
#include <vector>

#include "IGLDrawable.hpp"
#include "Sphere.hpp"
#include "GLTextureLoader.hpp"

class GLSphere : public IGLDrawable {

public:
    explicit GLSphere(Sphere const &sphere);
    ~GLSphere();
    GLSphere &operator=(const GLSphere &obj);
    GLSphere(GLSphere const &obj);

    void draw();

private:
    int _radius;
    Position _pos;
    Texture _texture;
    std::vector<GLfloat> _vertices;
    std::vector<GLfloat> _normals;
    std::vector<GLfloat> _texcoords;
    std::vector<GLushort> _indices;

};

#endif /*GLSPHERE_HPP_*/
