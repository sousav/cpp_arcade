/*
** Position.cpp for Shared in /Users/gmblucas/Desktop/Shared/cpp_arcade/sources
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Tue Mar 14 00:00:15 2017 Lucas Gambini
** Last update Sun Mar 26 17:41:37 2017 Sousa Victor
*/

#include "Color.hpp"

Color::Color (unsigned char const x, unsigned char const y, unsigned char const z, unsigned char const a) {
    this->_r = x;
    this->_g = y;
    this->_b = z;
    this->_a = a;
};

Color::~Color () {

};

Color::Color(const Color &obj) {
    this->_r = obj._r;
    this->_g = obj._g;
    this->_b = obj._b;
    this->_a = obj._a;
};

Color    &Color::operator=(const Color &obj) {
    this->_r = obj._r;
    this->_g = obj._g;
    this->_b = obj._b;
    this->_a = obj._a;
    return *this;
};

unsigned char Color::getR() const {
    return this->_r;
};
void Color::setR(unsigned char const r) {
    this->_r = r;
};

unsigned char Color::getG() const {
    return this->_g;
};
void Color::setG(unsigned char const g){
    this->_g = g;
};

unsigned char Color::getB() const {
    return this->_b;
};
void Color::setB(unsigned char const b){
    this->_b = b;
};

unsigned char Color::getA() const {
    return this->_a;
};
void Color::setA(unsigned char const a){
    this->_a = a;
};

void Color::setRGBA(unsigned char const x, unsigned char const y, unsigned char const z, unsigned char const a) {
    this->_r = x;
    this->_g = y;
    this->_b = z;
    this->_a = a;
}
