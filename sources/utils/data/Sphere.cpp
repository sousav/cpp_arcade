//
// Sphere.cpp for sphere in /Users/leandr_g/Documents/Shared folder/cpp_arcade/sources/utils/data/
//
// Made by Gaëtan Léandre
// Login   <leandr_g@epitech.eu>
//
// Started on  Fri Mar 17 02:01:08 2017 Gaëtan Léandre
// Last update Fri Mar 17 02:25:28 2017 Gaëtan Léandre
//

#include "Sphere.hpp"

Sphere::Sphere(Position const &pos, float radius, Texture const &text, unsigned int zIndex)
{
        this->_position = pos;
        this->_radius = radius;
        this->_texture = text;
        this->_zIndex = zIndex;
        this->_shape = DataType::Sphere;
}

Sphere::~Sphere()
{

}

Sphere &Sphere::operator=(const Sphere &obj)
{
    this->_position = obj._position;
    this->_radius = obj._radius;
    this->_texture = obj._texture;
    this->_zIndex = obj._zIndex;
    this->_shape = obj._shape;
    return *this;
}

Sphere::Sphere(Sphere const &obj)
{
    this->_position = obj._position;
    this->_radius = obj._radius;
    this->_texture = obj._texture;
    this->_zIndex = obj._zIndex;
    this->_shape = obj._shape;
}

float Sphere::getRadius() const
{
    return this->_radius;
}

void Sphere::setRadius(float radius)
{
    this->_radius = radius;
}

void Sphere::reset(void)
{
    this->_position = Position();
    this->_radius = 0;
    this->_texture = Texture();
    this->_zIndex = 0;
}
