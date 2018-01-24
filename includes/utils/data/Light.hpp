//
// Light.hpp for light in /Users/leandr_g/Documents/Shared folder/cpp_arcade/includes/utils/data/
//
// Made by Gaëtan Léandre
// Login   <leandr_g@epitech.eu>
//
// Started on  Fri Mar 17 01:15:01 2017 Gaëtan Léandre
// Last update Fri Mar 31 02:22:54 2017 Sousa Victor
//

#ifndef LIGHT_HPP_
#define LIGHT_HPP_

#include "AScene.hpp"

class Light : public AScene {
public:
    explicit Light(Position const &pos, float incX = 0, float incY = 0);
    ~Light();
    Light &operator=(const Light &obj);
    Light(Light const &obj);
    void reset(void);
};

#else

class Light;

#endif
