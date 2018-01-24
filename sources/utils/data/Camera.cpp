//
// Camera.cpp for camera in /Users/leandr_g/Documents/Shared folder/cpp_arcade/sources/utils/data/
//
// Made by Gaëtan Léandre
// Login   <leandr_g@epitech.eu>
//
// Started on  Fri Mar 17 01:05:52 2017 Gaëtan Léandre
// Last update Fri Mar 17 02:29:53 2017 Gaëtan Léandre
//

#include "Camera.hpp"

Camera::Camera(Position const &pos, float incX, float incY)
{
    this->_incX = incX;
    this->_incY = incY;
    this->_position = pos;
    this->_shape = DataType::Camera;
}

Camera::~Camera()
{

}

Camera &Camera::operator=(const Camera &obj)
{
    this->_incX = obj._incX;
    this->_incY = obj._incY;
    this->_position = obj._position;
    this->_shape = obj._shape;
    return *this;
}

Camera::Camera(Camera const &obj)
{
    this->_incX = obj._incX;
    this->_incY = obj._incY;
    this->_position = obj._position;
    this->_shape = obj._shape;
}

void Camera::reset(void)
{
    this->_incX = 0;
    this->_incY = 0;
    this->_position = Position();
}
