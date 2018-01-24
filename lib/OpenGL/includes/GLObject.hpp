//
// GLObject.hpp for  in /Users/vicostudio/Documents/Shared Folder/TEK2/CPP/cpp_arcade/lib/OpenGL/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sat Apr  1 01:03:26 2017 Sousa Victor
// Last update Sun Apr  9 03:21:58 2017 Sousa Victor
//

#ifndef GLOBJECT_HPP_
#define GLOBJECT_HPP_

#include <string>

#include "IGLDrawable.hpp"
#include "IGLMoveable.hpp"
#include "GLObjectLoader.hpp"

class GLObject: public IGLDrawable, public IGLMoveable {

public:
    explicit GLObject(std::string const &filepath);
    ~GLObject();
    GLObject &operator=(const GLObject &obj);
    GLObject(GLObject const &obj);

    void move(float x, float y, float z);
    void scale(float x, float y, float z);
    void rotate(float x, float y, float z);
    void setOffset(float x, float y, float z);
    void draw();

private:
    GLObjectData _data;

};

#else

class GLObject;

#endif /*GLOBJECT_HPP_*/
