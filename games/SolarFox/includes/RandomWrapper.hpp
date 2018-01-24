//
// RandomWrapper.hpp for  in /home/gambin_l/Shared/cpp_arcade/Game/Snake
//
// Made by lucas gambini
// Login   <gambin_l@epitech.net>
//
// Started on  Thu Mar 16 17:31:56 2017 lucas gambini
// Last update Thu Mar 16 17:32:07 2017 lucas gambini
//

#ifndef RANDOMWRAPPERDY_HPP_
#define RANDOMWRAPPERDY_HPP_

#include <stdlib.h>
#include <time.h>

class RandomWrapper {

public:
    RandomWrapper() {
        srand(time(NULL));
    }
    ~RandomWrapper() {

    }

    unsigned int getRand() const {
        return rand();
    }

};

#endif /*RANDOMWRAPPER_HPP_*/
