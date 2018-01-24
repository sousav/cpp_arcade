//
// GLObject.cpp for  in /Users/vicostudio/Documents/Shared Folder/TEK2/CPP/cpp_arcade/lib/OpenGL/sources/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sat Apr  1 01:09:47 2017 Sousa Victor
// Last update Thu Apr  6 00:08:23 2017 Sousa Victor
//

#include "GLObject.hpp"

GLObject::GLObject(std::string const &filepath) {
    this->_data = GLObjectLoader::load(filepath);
}

GLObject::~GLObject() {

}

GLObject &GLObject::operator=(const GLObject &obj) {
    this->_data = obj._data;
    return *this;
}

GLObject::GLObject(GLObject const &obj): _data(obj._data) {

}

void GLObject::move(float x, float y, float z) {
    this->_data.move(x, y, z);
}

void GLObject::scale(float x, float y, float z) {
    this->_data.scale(x, y, z);
}

void GLObject::rotate(float x, float y, float z) {
    this->_data.rotate(x, y, z);
}

void GLObject::setOffset(float x, float y, float z) {
    this->_data.setOffset(x, y, z);
}

void GLObject::draw() {
    this->_data.draw();
}
