//
// Cube.hpp for cube in /Users/leandr_g/Documents/Shared folder/cpp_arcade/includes/utils/data/
//
// Made by Gaëtan Léandre
// Login   <leandr_g@epitech.eu>
//
// Started on  Fri Mar 17 01:19:25 2017 Gaëtan Léandre
// Last update Tue Mar 28 18:24:36 2017 Gaëtan Léandre
//

#ifndef CUBE_HPP_
#define CUBE_HPP_

#include "AVisual.hpp"

class Cube : public AVisual {
public:
    explicit Cube(Position const &pos, Position const &size, Texture const &text = Texture(), unsigned int zIndex = 0, unsigned int id = 0);
    ~Cube();
    Cube &operator=(const Cube &obj);
    Cube(Cube const &obj);

    Position const &getSize() const;
    void setSize(Position const &size);
    bool operator==(Cube const &cube) const;
    bool inLine(double a, double new_a, double size) const;

    void reset(void);

protected:
    Position _size;
};

#else

class Cube;

#endif
