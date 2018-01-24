/*
** Position.hpp for Shared in /Users/gmblucas/Desktop/Shared/cpp_arcade/includes
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Mon Mar 13 23:51:23 2017 Lucas Gambini
** Last update	Sat Apr 08 23:17:27 2017 Full Name
*/

#ifndef POSITION_HPP_
#define POSITION_HPP_

class Position {

private:
    double _x;
    double _y;
    double _z;

public:
    Position (double const x = 0, double const y = 0, double const z = 0);
    ~Position ();
    Position(const Position &obj);
    Position    &operator=(const Position &obj);
    bool    operator==(const Position &obj) const;

    double getX() const;
    void setX(double const x);

    double getY() const;
    void setY(double const y);

    double getZ() const;
    void setZ(double const z);

};

Position operator+(Position const &a, Position const &b);
Position operator-(Position const &a, Position const &b);
Position operator/(Position const &a, int b);
Position operator*(Position const &a, int b);

#else

class Position;

#endif /* !POSITION_HPP_ */
