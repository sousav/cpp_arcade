//
// AScene.hpp for ascene in /Users/leandr_g/Documents/Shared folder/cpp_arcade/includes/utils/data/
//
// Made by Gaëtan Léandre
// Login   <leandr_g@epitech.eu>
//
// Started on  Fri Mar 17 00:42:06 2017 Gaëtan Léandre
// Last update Fri Mar 17 02:33:59 2017 Gaëtan Léandre
//

#ifndef ASCENE_HPP_
#define ASCENE_HPP_

#include "AData.hpp"

class AScene : public AData {
public:
    virtual ~AScene () {};

    float getIncX() const;
    virtual void setIncX(float incX);

    float getIncY() const;
    virtual void setIncY(float incY);

    virtual void reset(void) = 0;


protected:
    float _incX;
    float _incY;
};

#else

class AScene;

#endif
