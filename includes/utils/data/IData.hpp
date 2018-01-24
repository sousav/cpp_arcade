/*
** IData.hpp for Shared in /Users/gmblucas/Desktop/Shared/cpp_arcade/includes/utils/data
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Thu Mar 16 21:45:36 2017 Lucas Gambini
** Last update	Fri Mar 17 02:34:03 2017 Full Name
*/

#ifndef IDATA_HPP_
#define IDATA_HPP_

#include "Position.hpp"
#include "Texture.hpp"

enum class DataType {
    Sphere,
    Cube,
    Camera,
    Light,
    Music,
    Text
};

class IData {

public:
    virtual ~IData () {};

    virtual DataType const &getShape() const = 0;
    virtual void setShape(DataType const &shape) = 0;

    virtual Position const &getPosition() const = 0;
    virtual void setPosition(Position const &position) = 0;
    virtual void reset(void) = 0;


};

#else

class IData;
enum class DataType;


#endif /* !IDATA_HPP_ */
