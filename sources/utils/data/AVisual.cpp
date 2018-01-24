/*
** AVisual.cpp for Shared in /Users/gmblucas/Desktop/Shared/cpp_arcade/sources/utils/data
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Tue Mar 14 02:45:49 2017 Lucas Gambini
** Last update Wed Mar 29 16:05:36 2017 Lucas Gambini
*/

#include "AVisual.hpp"

Texture const &AVisual::getTexture() const {
    return this->_texture;
}

void AVisual::setTexture(Texture const &texture) {
    this->_texture = texture;
}


unsigned int AVisual::getZIndex() const {
    return this->_zIndex;
}

void AVisual::setZIndex(unsigned int zIndex) {
    this->_zIndex = zIndex;
}

void AVisual::setRotation(int rotation) {
    this->_texture.setRotation(rotation);
}

unsigned int AVisual::getId() const {
    return this->_id;
}

void AVisual::setId(unsigned int id) {
    this->_id = id;
}
