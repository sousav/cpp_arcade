//
// 3DModel.cpp for  in /Users/vicostudio/Documents/Shared Folder/TEK2/CPP/cpp_arcade/sources/utils/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sat Apr  1 23:22:48 2017 Sousa Victor
// Last update Sat Apr  1 23:38:19 2017 Sousa Victor
//

#include "Model3D.hpp"

Model3D::Model3D(std::string const &object, Position const &position, Position const &scale, Position const &rotation) {
    this->_object = object;
    this->_scale = scale;
    this->_position = position;
    this->_rotation = rotation;
}

Model3D::~Model3D () {

}

Model3D::Model3D(const Model3D &obj) {
    this->_object = obj._object;
    this->_scale = obj._scale;
    this->_position = obj._position;
    this->_rotation = obj._rotation;
}

Model3D    &Model3D::operator=(const Model3D &obj) {
    this->_object = obj._object;
    this->_scale = obj._scale;
    this->_position = obj._position;
    this->_rotation = obj._rotation;
    return *this;
}


void Model3D::setObject(std::string const &object) {
    this->_object = object;
}

std::string const &Model3D::getObject(void) const {
    return this->_object;
}


void Model3D::setScale(Position const &scale) {
    this->_scale = scale;
}

void Model3D::setScaleX(double x) {
    this->_scale.setX(x);
}

void Model3D::setScaleY(double y) {
    this->_scale.setY(y);
}

void Model3D::setScaleZ(double z) {
    this->_scale.setZ(z);
}

Position const &Model3D::getScale(void) const {
    return this->_scale;
}


void Model3D::setPosition(Position const &position) {
    this->_position = position;
}

void Model3D::setPositionX(double x) {
    this->_position.setX(x);
}

void Model3D::setPositionY(double y) {
    this->_position.setY(y);
}

void Model3D::setPositionZ(double z) {
    this->_position.setZ(z);
}

Position const &Model3D::getPosition(void) const {
    return this->_position;
}


void Model3D::setRotation(Position const &rotation) {
    this->_rotation = rotation;
}

void Model3D::setRotationX(double x) {
    this->_rotation.setX(x);
}

void Model3D::setRotationY(double y) {
    this->_rotation.setY(y);
}

void Model3D::setRotationZ(double z) {
    this->_rotation.setZ(z);
}

Position const &Model3D::getRotation(void) const {
    return this->_rotation;
}
