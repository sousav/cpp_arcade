//
// AScene.cpp for AScene in /Users/leandr_g/Documents/Shared folder/cpp_arcade/sources/utils/data/
//
// Made by Gaëtan Léandre
// Login   <leandr_g@epitech.eu>
//
// Started on  Fri Mar 17 00:47:54 2017 Gaëtan Léandre
// Last update Fri Mar 17 01:11:12 2017 Gaëtan Léandre
//

#include "AScene.hpp"

float AScene::getIncX() const
{
    return (this->_incX);
}

void AScene::setIncX(float incX)
{
    this->_incX = incX;
}

float AScene::getIncY() const
{
    return (this->_incY);
}

void AScene::setIncY(float incY)
{
    this->_incY = incY;
}
