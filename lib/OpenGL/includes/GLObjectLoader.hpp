//
// GLObjectLoader.hpp for  in /Users/vicostudio/Documents/Shared Folder/TEK2/CPP/cpp_arcade/lib/OpenGL/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sat Apr  1 03:11:43 2017 Sousa Victor
// Last update Sun Apr  9 21:10:22 2017 Sousa Victor
//

#ifndef GLOBJECTLOADER_HPP_
#define GLOBJECTLOADER_HPP_

#include <map>
#include <string>
#include <iostream>

#include "GLObjectData.hpp"

class GLObjectLoader {

public:
    ~GLObjectLoader();

    static GLObjectData load(std::string const & filename);
    static void clean();

private:
    GLObjectLoader();

    static std::map<std::string, GLObjectData> _objectMap;

};

#else

class GLObjectLoader;

#endif /*GLOBJECTLOADER_HPP_*/
