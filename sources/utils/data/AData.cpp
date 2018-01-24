/*
** AData.cpp for Shared in /Users/gmblucas/Desktop/Shared/cpp_arcade/sources
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Tue Mar 14 01:22:47 2017 Lucas Gambini
** Last update Tue Mar 14 02:46:59 2017 Lucas Gambini
*/

#include "AData.hpp"

DataType const &AData::getShape() const {
    return this->_shape;
}

void AData::setShape(DataType const &shape) {
    this->_shape = shape;
}

Position const &AData::getPosition() const {
    return this->_position;
}

void AData::setPosition(Position const &position) {
    this->_position = position;
}

void AData::setPositionX(double const x) {
    this->_position.setX(x);
}

void AData::setPositionY(double const y) {
    this->_position.setY(y);
}

void AData::setPositionZ(double const z) {
    this->_position.setZ(z);
}
