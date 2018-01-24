//
// IGLDrawable.hpp for  in /Users/vicostudio/Documents/Shared Folder/TEK2/CPP/cpp_arcade/lib/OpenGL/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sun Apr  9 03:16:08 2017 Sousa Victor
// Last update Sun Apr  9 03:20:55 2017 Sousa Victor
//

#ifndef IGLDRAWABLE_HPP_
#define IGLDRAWABLE_HPP_

class IGLDrawable {

public:
    virtual ~IGLDrawable () {};

    virtual void draw(void) = 0;

};

#else

class IData;

#endif /*IGLDRAWABLE_HPP_*/
