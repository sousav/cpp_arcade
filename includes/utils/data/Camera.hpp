//
// Camera.hpp for Camera in /Users/leandr_g/Documents/Shared folder/cpp_arcade/includes/utils/data/
//
// Made by Gaëtan Léandre
// Login   <leandr_g@epitech.eu>
//
// Started on  Fri Mar 17 00:54:54 2017 Gaëtan Léandre
// Last update Sat Mar 25 17:57:02 2017 Sousa Victor
//

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "AScene.hpp"

class Camera : public AScene {
public: 
    explicit Camera(Position const &pos, float incX = 0, float incY = 0);
    ~Camera();
    Camera &operator=(const Camera &obj);
    Camera(Camera const &camera);
    void reset(void);
};

#else

class Camera;

#endif
