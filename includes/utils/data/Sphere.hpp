//
// Sphere.hpp for sphere in /Users/leandr_g/Documents/Shared folder/cpp_arcade/includes/utils/data/
//
// Made by Gaëtan Léandre
// Login   <leandr_g@epitech.eu>
//
// Started on  Fri Mar 17 01:50:18 2017 Gaëtan Léandre
// Last update Fri Mar 17 02:41:14 2017 Gaëtan Léandre
//

#ifndef SPHERE_HPP_
#define SHPERE_HPP_

#include "AVisual.hpp"

class Sphere : public AVisual {
public:
    explicit Sphere(Position const &pos, float radius, Texture const &text = Texture(), unsigned int zIndex = 0);
    ~Sphere();
    Sphere &operator=(const Sphere &obj);
    Sphere(Sphere const &obj);

    float getRadius() const;
    void setRadius(float radius);

    void reset(void);

protected:
    float _radius;
};

#else

class Sphere;

#endif
