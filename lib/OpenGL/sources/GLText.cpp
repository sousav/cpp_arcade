//
// GLText.cpp for  in /Users/vicostudio/Documents/Shared Folder/TEK2/CPP/cpp_arcade/lib/OpenGL/sources/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Mon Mar 27 20:51:46 2017 Sousa Victor
// Last update Sun Apr  9 03:26:58 2017 Sousa Victor
//

#include "GLText.hpp"

FTGLPixmapFont *GLText::_font = NULL;
GLText::GLText(Text const &text): _text(text) {
    if (this->_font == NULL) {
        this->_font = new FTGLPixmapFont("./Assets/Fonts/ARCADEPI.TTF");
    }
    this->_window = NULL;
}

GLText::~GLText() {

}

GLText &GLText::operator=(const GLText &obj) {
    this->_text = obj._text;
    if (this->_font == NULL) {
        this->_font = new FTGLPixmapFont("./Assets/Fonts/ARCADEPI.TTF");
    }
    this->_window = obj._window;
    return *this;
}

GLText::GLText(GLText const &obj): _text(obj._text) {
    if (this->_font == NULL) {
        this->_font = new FTGLPixmapFont("./Assets/Fonts/ARCADEPI.TTF");
    }
    this->_window = obj._window;
}

void GLText::setWindow(GLFWwindow *window) {
    this->_window = window;
}

void GLText::draw() {
    glDisable(GL_LIGHTING);
    glPushMatrix();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        int width, height;
        glfwGetWindowSize(_window, &width, &height);
        gluOrtho2D(0, width, 0, height);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glColor4f((double)(this->_text.getTexture().getColor().getR() / 255.0),
                  (double)(this->_text.getTexture().getColor().getG() / 255.0),
                  (double)(this->_text.getTexture().getColor().getB() / 255.0),
                  (double)(this->_text.getTexture().getColor().getA() / 255.0));
        this->_font->FaceSize(this->_text.getSize());
        FTSimpleLayout layout;
        layout.SetFont(this->_font);
        layout.SetAlignment(this->_text.getAlign() == Text::Align::LEFT ? FTGL::ALIGN_LEFT :
                            this->_text.getAlign() == Text::Align::CENTER ? FTGL::ALIGN_CENTER :
                            this->_text.getAlign() == Text::Align::RIGHT ? FTGL::ALIGN_RIGHT : FTGL::ALIGN_CENTER);
        layout.SetLineLength(width);
        glRasterPos2f(0, height - ((this->_text.getPosition().getY() / 100.0) * height) - this->_font->LineHeight() / 2);
        layout.Render(this->_text.getText().data());
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(90, (double)(width / height), 1, 1000);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    glPopMatrix();
    glEnable(GL_LIGHTING);
}
