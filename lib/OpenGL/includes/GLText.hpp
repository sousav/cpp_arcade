//
// GLText.hpp for  in /Users/vicostudio/Documents/Shared Folder/TEK2/CPP/cpp_arcade/lib/OpenGL/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Mon Mar 27 20:47:53 2017 Sousa Victor
// Last update Sun Apr  9 03:26:16 2017 Sousa Victor
//

#ifndef GLTEXT_HPP_
#define GLTEXT_HPP_

#ifdef __APPLE__
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
#else
# ifdef _WIN32
   #include <windows.h>
# endif
# include <GL/gl.h>
# include <GL/glu.h>
#endif
#include <GLFW/glfw3.h>
#include <FTGL/ftgl.h>

#include "IGLDrawable.hpp"
#include "Text.hpp"

class GLText : public IGLDrawable {

public:
    explicit GLText(Text const &text);
    ~GLText();
    GLText &operator=(const GLText &obj);
    GLText(GLText const &obj);

    void setWindow(GLFWwindow *_window);
    void draw();

private:
    GLFWwindow *_window;
    Text _text;
    static FTGLPixmapFont *_font;

};

#endif /*GLTEXT_HPP_*/
