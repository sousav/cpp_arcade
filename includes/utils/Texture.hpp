/*
** Texture.hpp for Shared in /Users/gmblucas/Desktop/Shared/cpp_arcade/includes/utils
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Tue Mar 14 00:44:40 2017 Lucas Gambini
** Last update	Thu Mar 23 11:48:39 2017 Full Name
*/

#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include <string>
#include "Color.hpp"
#include "Model3D.hpp"

class Texture {

public:
    Texture (Color const & color = Color());
    Texture (std::string const & sprite, Color const & color = Color(), int rotation = 0, Model3D const &model = Model3D());
    virtual ~Texture ();
    Texture(const Texture &obj);
    Texture    &operator=(const Texture &obj);

    Color const &getColor() const;
    void setColor(Color const &color);

    std::string const &getSprite() const;
    void setSprite(std::string const &sprite);

    int const &getRotation() const;
    void setRotation(int rotation);

    Model3D const &getModel() const;
    void setModel(Model3D const &model);

private:
    Color _color;
    std::string _sprite;
    Model3D _model;
    int _rotation;

};

#else

class Texture;

#endif /* !TEXTURE_HPP_ */
