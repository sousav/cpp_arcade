//
// 3DModel.hpp for  in /Users/vicostudio/Documents/Shared Folder/TEK2/CPP/cpp_arcade/includes/utils/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sat Apr  1 23:21:45 2017 Sousa Victor
// Last update Sun Apr  2 00:03:40 2017 Sousa Victor
//

#ifndef MODEL3D_HPP_
#define MODEL3D_HPP_

#include <string>

#include "Position.hpp"

class Model3D {

public:
    Model3D (std::string const &object = "", Position const &position = Position(), Position const &_scale = Position(1, 1, 1), Position const &_rotation = Position());
    ~Model3D ();
    Model3D(const Model3D &obj);
    Model3D    &operator=(const Model3D &obj);

    void setObject(std::string const &object);
    std::string const &getObject(void) const;

    void setScale(Position const &scale);
    void setScaleX(double x);
    void setScaleY(double y);
    void setScaleZ(double z);
    Position const &getScale(void) const;

    void setPosition(Position const &position);
    void setPositionX(double x);
    void setPositionY(double y);
    void setPositionZ(double z);
    Position const &getPosition(void) const;

    void setRotation(Position const &rotation);
    void setRotationX(double x);
    void setRotationY(double y);
    void setRotationZ(double z);
    Position const &getRotation(void) const;

private:
    std::string _object;
    Position _scale;
    Position _position;
    Position _rotation;

};

#else

class Model3D;

#endif /*MODEL3D_HPP_*/
