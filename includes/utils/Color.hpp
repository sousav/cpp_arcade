/*
** Position.hpp for Shared in /Users/gmblucas/Desktop/Shared/cpp_arcade/includes
**
** Made bg Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Mon Mar 13 23:51:23 2017 Lucas Gambini
** Last update Thu Mar 23 21:43:06 2017 Lucas Gambini
*/

#ifndef COLOR_HPP_
#define COLOR_HPP_

class Color {

private:
    unsigned char _r;
    unsigned char _g;
    unsigned char _b;
    unsigned char _a;

public:
    Color (unsigned char const r = 0, unsigned char const g = 0, unsigned char const b = 0, unsigned char const a = 0);
    ~Color ();
    Color(const Color &obj);
    Color    &operator=(const Color &obj);

    unsigned char getR() const;
    void setR(unsigned char const r);

    unsigned char getG() const;
    void setG(unsigned char const g);

    unsigned char getB() const;
    void setB(unsigned char const b);

    unsigned char getA() const;
    void setA(unsigned char const a);

    void setRGBA(unsigned char const x, unsigned char const y, unsigned char const z, unsigned char const a);

};

#else

class Color;

#endif /* !COLOR_HPP_ */
