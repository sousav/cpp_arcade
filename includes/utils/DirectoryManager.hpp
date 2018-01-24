/*
** DirectoryManager.hpp for Shared in /Users/gmblucas/Desktop/Shared/cpp_arcade/includes/utils
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Fri Mar 17 00:25:43 2017 Lucas Gambini
** Last update Fri Mar 17 01:12:02 2017 Lucas Gambini
*/

#ifndef DIRECTORYMANAGER_HPP_
#define DIRECTORYMANAGER_HPP_

# include "dirent.h"

# include <vector>
# include <string>
# include <iostream>

class DirectoryManager {

public:
    DirectoryManager ();
    virtual ~DirectoryManager ();

    static std::vector<std::string> getFilesInDir(std::string const &dir);

private:
    static DIR *openDir(std::string const &dir);

};

#endif /* !DIRECTORYMANAGER_HPP_ */
