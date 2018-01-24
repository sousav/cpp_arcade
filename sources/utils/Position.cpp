/*
** Position.cpp for Shared in /Users/gmblucas/Desktop/Shared/cpp_arcade/sources
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Tue Mar 14 00:00:15 2017 Lucas Gambini
** Last update	Sat Apr 08 23:19:37 2017 Full Name
*/

#include "Position.hpp"

Position::Position (double const x, double const y, double const z) {
    this->_x = x;
    this->_y = y;
    this->_z = z;
};

Position::~Position () {

};

Position::Position(const Position &obj) {
    this->_x = obj._x;
    this->_y = obj._y;
    this->_z = obj._z;
};

Position    &Position::operator=(const Position &obj) {
    this->_x = obj._x;
    this->_y = obj._y;
    this->_z = obj._z;
    return *this;
};

bool		Position::operator==(const Position &obj) const {
    return (_x == obj._x && _y == obj._y && _z == obj._z);
};

double Position::getX() const {
    return this->_x;
};
void Position::setX(double const x) {
    this->_x = x;
};

double Position::getY() const {
    return this->_y;
};
void Position::setY(double const y){
    this->_y = y;
};

double Position::getZ() const {
    return this->_z;
};
void Position::setZ(double const z){
    this->_z = z;
};

Position operator+(Position const &a, Position const &b)
{
    Position tmp(a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ());
    return (tmp);
}

Position operator-(Position const &a, Position const &b)
{
    Position tmp(a.getX() - b.getX(), a.getY() - b.getY(), a.getZ() - b.getZ());
    return (tmp);
}

Position operator/(Position const &a, int b)
{
    Position tmp(a.getX() / b, a.getY() / b, a.getZ() / b);
    return (tmp);
}

Position operator*(Position const &a, int b)
{
    Position tmp(a.getX() * b, a.getY() * b, a.getZ() * b);
    return (tmp);
}
