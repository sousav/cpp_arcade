/*
** Visual.hpp for Shared in /Users/gmblucas/Desktop/Shared/cpp_arcade/includes/utils/data
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Tue Mar 14 02:40:12 2017 Lucas Gambini
** Last update Wed Mar 29 15:27:07 2017 Lucas Gambini
*/

#ifndef VISUAL_HPP_
#define VISUAL_HPP_

#include "AData.hpp"

class AVisual: public AData {

public:
    virtual ~AVisual () {};

    Texture const &getTexture() const;
    virtual void setTexture(Texture const &texture);

    virtual void setRotation(int rotation);

    unsigned int getZIndex() const;
    virtual void setZIndex(unsigned int zIndex);

    unsigned int getId() const;
    virtual void setId(unsigned int id);

    virtual void reset(void) = 0;

protected:
    Texture _texture;
    unsigned int _zIndex;
    unsigned int _id;

};

#else

class AVisual;

#endif /* !VISUAL_HPP_ */
