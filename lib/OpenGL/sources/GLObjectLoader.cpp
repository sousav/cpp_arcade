//
// GLObjectLoader.cpp for  in /Users/vicostudio/Documents/Shared Folder/TEK2/CPP/cpp_arcade/lib/OpenGL/sources/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sat Apr  1 03:19:21 2017 Sousa Victor
// Last update Sun Apr  9 21:12:17 2017 Sousa Victor
//

#include "GLObjectLoader.hpp"

std::map<std::string, GLObjectData> GLObjectLoader::_objectMap;
GLObjectData GLObjectLoader::load(std::string const & filename) {
    if (filename != "") {
        std::map<std::string,GLObjectData>::iterator it = GLObjectLoader::_objectMap.find(filename);
        if (it != GLObjectLoader::_objectMap.end()) {
            return it->second;
        } else {
            std::cout << "loading: " << filename << std::endl;
            GLObjectLoader::_objectMap[filename] = GLObjectData(filename);
            return GLObjectLoader::_objectMap[filename];
        }
    }
    return GLObjectData();
}

void GLObjectLoader::clean() {
    GLObjectLoader::_objectMap.clear();
}
