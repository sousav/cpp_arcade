//
// main.cpp for  in /home/sousa_v/rendu/cpp_arcade
//
// Made by Victor Sousa
// Login   <sousa_v@epitech.net>
//
// Started on  Mon Mar 13 22:40:38 2017 Victor Sousa
// Last update Sat Apr  8 18:02:42 2017 Gaëtan Léandre
//

#include "Arcade.hpp"

int main(int const ac, char const * const * const av)
{
    if (ac != 2)
    {
        std::cerr << "Usage: " << av[0] << " [Startup Library]" << std::endl;
        return EXIT_FAILURE;
    }
    Arcade arcade;
    arcade.Setup();
    arcade.Start(av[1]);
    arcade.mainLoop();
    return EXIT_SUCCESS;
}
