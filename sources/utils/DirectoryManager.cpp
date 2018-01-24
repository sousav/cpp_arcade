/*
** DirectoryManager.cpp for Shared in /Users/gmblucas/Desktop/Shared/cpp_arcade/sources/utils
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Fri Mar 17 00:25:32 2017 Lucas Gambini
** Last update Fri Mar 17 15:40:18 2017 Lucas Gambini
*/

# include "DirectoryManager.hpp"

DirectoryManager::DirectoryManager()
{

}

DirectoryManager::~DirectoryManager()
{

}

std::vector<std::string> DirectoryManager::getFilesInDir(std::string const &dir)
{
    std::vector<std::string> files;
    DIR *_dir = NULL;
    struct dirent *dirent;
    std::string name;

    _dir = openDir(dir);
    if (!_dir)
        return files;
    while ((dirent = readdir(_dir)))
    {
        name.assign(dirent->d_name);
        if (dirent->d_type == DT_REG && name.substr(name.length() - 3) == ".so")
            files.push_back(dir + name);
    }
    closedir(_dir);
    return files;
}

DIR *DirectoryManager::openDir(std::string const &dir)
{
    DIR *_dir;

    if ((_dir = opendir(dir.c_str())) == NULL)
        return NULL;
    return _dir;
}
