//
// IGLMoveable.hpp for  in /Users/vicostudio/Documents/Shared Folder/TEK2/CPP/cpp_arcade/lib/OpenGL/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sun Apr  9 03:22:12 2017 Sousa Victor
// Last update Sun Apr  9 03:22:46 2017 Sousa Victor
//

#ifndef IGLMOVEABLE_HPP_
#define IGLMOVEABLE_HPP_

class IGLMoveable {

public:
    virtual ~IGLMoveable () {};

    void move(float x, float y, float z);
    void scale(float x, float y, float z);
    void rotate(float x, float y, float z);
    void setOffset(float x, float y, float z);

};

#else

class IData;

#endif /*IGLMOVEABLE_HPP_*/
