//
// Light.cpp for light in /Users/leandr_g/Documents/Shared folder/cpp_arcade/sources/utils/data/
//
// Made by Gaëtan Léandre
// Login   <leandr_g@epitech.eu>
//
// Started on  Fri Mar 17 01:17:16 2017 Gaëtan Léandre
// Last update Fri Mar 17 02:27:46 2017 Gaëtan Léandre
//

#include "Light.hpp"

Light::Light(Position const &pos, float incX, float incY)
{
    this->_incX = incX;
    this->_incY = incY;
    this->_position = pos;
    this->_shape = DataType::Light;
}

Light::~Light()
{

}

Light &Light::operator=(const Light &obj)
{
    this->_incX = obj._incX;
    this->_incY = obj._incY;
    this->_position = obj._position;
    this->_shape = obj._shape;
    return *this;
}

Light::Light(Light const &obj)
{
    this->_incX = obj._incX;
    this->_incY = obj._incY;
    this->_position = obj._position;
    this->_shape = obj._shape;
}

void Light::reset(void)
{
    this->_incX = 0;
    this->_incY = 0;
    this->_position = Position();
}
