/*
** Data.hpp for Shared in /Users/gmblucas/Desktop/Shared/cpp_arcade/includes
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Mon Mar 13 23:36:43 2017 Lucas Gambini
** Last update Thu Mar 16 22:20:43 2017 Lucas Gambini
*/

#ifndef ADATA_HPP_
#define ADATA_HPP_

#include "IData.hpp"

class AData : public IData {

public:
    virtual ~AData () {};

    DataType const &getShape() const;
    virtual void setShape(DataType const &shape);

    Position const &getPosition() const;
    virtual void setPosition(Position const &position);

    virtual void setPositionX(double const x);
    virtual void setPositionY(double const y);
    virtual void setPositionZ(double const z);

    virtual void reset(void) = 0;

protected:
    DataType _shape;
    Position _position;

};

#else

class AData;

#endif /* !ADATA_HPP_ */
