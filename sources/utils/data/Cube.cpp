//
// Cube.cpp for cube in /Users/leandr_g/Documents/Shared folder/cpp_arcade/sources/utils/data/
//
// Made by Gaëtan Léandre
// Login   <leandr_g@epitech.eu>
//
// Started on  Fri Mar 17 01:26:23 2017 Gaëtan Léandre
// Last update Tue Mar 28 18:24:22 2017 Gaëtan Léandre
//

#include "Cube.hpp"

#include <iostream>

Cube::Cube(Position const &pos, Position const &size, Texture const &text, unsigned int zIndex, unsigned int id)
{
    this->_size = size;
    this->_position = pos;
    this->_texture = text;
    this->_zIndex = zIndex;
    this->_shape = DataType::Cube;
    this->_id = id;
}

Cube::~Cube()
{

}

Cube &Cube::operator=(const Cube &obj)
{
    this->_size = obj._size;
    this->_position = obj._position;
    this->_texture = obj._texture;
    this->_zIndex = obj._zIndex;
    this->_shape = obj._shape;
    this->_id = obj._id;
    return *this;
}

Cube::Cube(Cube const &obj)
{
    this->_size = obj._size;
    this->_position = obj._position;
    this->_texture = obj._texture;
    this->_zIndex = obj._zIndex;
    this->_shape = obj._shape;
    this->_id = obj._id;
}

Position const &Cube::getSize() const
{
    return this->_size;
}

void Cube::setSize(Position const &size)
{
    this->_size = size;
}

void Cube::reset(void) {
    this->_size = 0;
    this->_position = Position();
    this->_texture = Texture();
    this->_zIndex = 0;
}

bool Cube::inLine(double a, double new_a, double size) const
{
    return (a >= new_a && a <= new_a + size);
}

bool Cube::operator==(Cube const &cube) const
{
    bool xIn = inLine(cube.getPosition().getX(), this->getPosition().getX(), this->getSize().getX())
    || inLine(this->getPosition().getX(), cube.getPosition().getX(), cube.getSize().getX());

    bool yIn = inLine(cube.getPosition().getY(), this->getPosition().getY(), this->getSize().getY())
    || inLine(this->getPosition().getY(), cube.getPosition().getY(), cube.getSize().getY());

    bool zIn = inLine(cube.getPosition().getZ(), this->getPosition().getZ(), this->getSize().getZ())
    || inLine(this->getPosition().getZ(), cube.getPosition().getZ(), cube.getSize().getZ());

    return (xIn && yIn && zIn);
}
