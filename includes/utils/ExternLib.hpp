/*
** ExternLib.hpp for Shared in /Users/gmblucas/Desktop/Shared/cpp_arcade/includes/utils
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Tue Mar 14 03:59:02 2017 Lucas Gambini
** Last update Sat Apr 08 14:35:02 2017 Lucas Gambini
*/

#ifndef EXTERNLIB_HPP_
#define EXTERNLIB_HPP_

#include <iostream>
#include <dlfcn.h>
#include <Exceptions.hpp>

class ExternLib {

public:

    ExternLib (char const * filename, int flags) {
        this->_lib = dlopen(filename, flags);
        if (!this->_lib) {
            try {
                throw InvalidDlOpen(dlerror());
            } catch (std::exception const &e){
                _lib = NULL;
                std::cerr << e.what() << std::endl;
            }
        }
    };

    ~ExternLib () {
        //if (_lib)
            //dlclose(this->_lib);
    }

    void *getLib() const {
        return this->_lib;
    }

private:
    void *_lib;

};

#endif /* !EXTERNLIB_HPP_ */
