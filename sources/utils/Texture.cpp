/*
** Texture.cpp for Shared in /Users/gmblucas/Desktop/Shared/cpp_arcade/sources/utils
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Tue Mar 14 00:49:45 2017 Lucas Gambini
** Last update	Thu Mar 23 11:49:01 2017 Full Name
*/

#include "Texture.hpp"

Texture::Texture (Color const & color) {
    this->_color = color;
    this->_sprite = "";
    this->_rotation = 0;
}

Texture::Texture (std::string const & sprite, Color const & color, int rotation, Model3D const &model) {
    this->_color = color;
    this->_sprite = sprite;
    this->_rotation = rotation;
    this->_model = model;
}

Texture::~Texture () {

}

Texture::Texture(const Texture &obj) {
    this->_color = obj._color;
    this->_sprite = obj._sprite;
    this->_rotation = obj._rotation;
    this->_model = obj._model;
}

Texture    &Texture::operator=(const Texture &obj) {
    this->_color = obj._color;
    this->_sprite = obj._sprite;
    this->_rotation = obj._rotation;
    this->_model = obj._model;
    return *this;
}


Color const &Texture::getColor() const {
    return this->_color;
}

void Texture::setColor(Color const &color) {
    this->_color = color;
}


std::string const &Texture::getSprite() const {
    return this->_sprite;
}

void Texture::setSprite(std::string const &sprite) {
    this->_sprite = sprite;
}

int const &Texture::getRotation() const {
    return this->_rotation;
}

void Texture::setRotation(int rotation) {
    this->_rotation = rotation;
}

Model3D const &Texture::getModel() const {
    return this->_model;
}

void Texture::setModel(Model3D const &model) {
    this->_model = model;
}
