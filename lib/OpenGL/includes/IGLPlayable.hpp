//
// IGLPlayable.hpp for  in /Users/vicostudio/Documents/Shared Folder/TEK2/CPP/cpp_arcade/lib/OpenGL/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sun Apr  9 03:19:54 2017 Sousa Victor
// Last update Sun Apr  9 03:19:59 2017 Sousa Victor
//

#ifndef IGLPLAYABLE_HPP_
#define IGLPLAYABLE_HPP_

class IGLPlayable {

public:
    virtual ~IGLPlayable () {};

    virtual void play(void) const = 0;

};

#else

class IData;

#endif /*IGLPLAYABLE_HPP_*/
