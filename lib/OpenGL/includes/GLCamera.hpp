//
// GLCamera.hpp for  in /Users/vicostudio/Documents/Shared Folder/TEK2/CPP/cpp_arcade/lib/OpenGL/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sun Mar 26 01:06:54 2017 Sousa Victor
// Last update Fri Apr  7 03:18:21 2017 Sousa Victor
//

#ifndef GLCAMERA_HPP_
#define GLCAMERA_HPP_

#ifdef __APPLE__
# include <GL/glew.h>
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
#else
# ifdef _WIN32
   #include <windows.h>
# endif
# include <GL/glew.h>
# include <GL/gl.h>
# include <GL/glu.h>
#endif
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <math.h>
#include <vector>

#include "Camera.hpp"

# define DTR(angle) ((angle) / 180.0 * M_PI)

class GLCamera {

public:
    GLCamera();
    GLCamera(Camera const &camera);
    GLCamera(std::vector <AData *> const &data);
    ~GLCamera();
    GLCamera &operator=(const GLCamera &obj);
    GLCamera(GLCamera const &obj);

    void setupView() const;

private:
    bool _hasCamera;
    Camera _camera;

};


#endif /*GLCAMERA_HPP_*/
