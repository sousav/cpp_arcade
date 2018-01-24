//
// GLCube.cpp for  in /Users/vicostudio/Documents/Shared Folder/TEK2/CPP/cpp_arcade/lib/OpenGL/sources/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sun Mar 26 00:43:11 2017 Sousa Victor
// Last update Sun Apr  9 03:17:39 2017 Sousa Victor
//

#include "GLCube.hpp"

GLCube::GLCube(Cube const &cube): _cube(cube) {

}

GLCube::~GLCube() {

}

GLCube &GLCube::operator=(const GLCube &obj) {
    this->_cube = obj._cube;
    return *this;
}

GLCube::GLCube(GLCube const &obj): _cube(obj._cube) {

}


void GLCube::draw() {
    int x = this->_cube.getPosition().getX();
    int y = this->_cube.getPosition().getY();
    int z = this->_cube.getPosition().getZ();
    int sizex = this->_cube.getSize().getX();
    int sizey = this->_cube.getSize().getY();
    int sizez = this->_cube.getSize().getZ();
    GLuint tex = GLTextureLoader::load(this->_cube.getTexture().getSprite());
    Color const & color = this->_cube.getTexture().getColor();

    glDisable(GL_LIGHTING);
    glPushMatrix();
    glColor4f(1,1,1,1);
    if (tex != 0) {
        glEnable(GL_TEXTURE_2D);
    } else {
        glDisable(GL_TEXTURE_2D);
    }

    if (tex != 0) { glBindTexture(GL_TEXTURE_2D, tex); }
    glBegin(GL_QUADS);
    glNormal3f(1.0f, 0.0f, 0.0f);
    if (tex == 0) { glColor4f((double)(color.getR() / 255.0), (double)(color.getG() / 255.0), (double)(color.getB() / 255.0), (double)(color.getA() / 255.0)); }
    if (tex != 0) { glTexCoord2d(0,1); }  glVertex3d(x + sizex,    y + sizey,     z + sizez);
    if (tex != 0) { glTexCoord2d(0,0); }  glVertex3d(x + sizex,    y + sizey,     z);
    if (tex != 0) { glTexCoord2d(1,0); }  glVertex3d(x,            y + sizey,     z);
    if (tex != 0) { glTexCoord2d(1,1); }  glVertex3d(x,            y + sizey,     z + sizez);
    glEnd();

    if (tex != 0) { glBindTexture(GL_TEXTURE_2D, tex); }
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    if (tex == 0) { glColor4f((double)(color.getR() / 255.0), (double)(color.getG() / 255.0), (double)(color.getB() / 255.0), (double)(color.getA() / 255.0)); }
    if (tex != 0) { glTexCoord2d(0,1); }  glVertex3d(x + sizex,    y,             z + sizez);
    if (tex != 0) { glTexCoord2d(0,0); }  glVertex3d(x + sizex,    y,             z);
    if (tex != 0) { glTexCoord2d(1,0); }  glVertex3d(x + sizex,    y + sizey,     z);
    if (tex != 0) { glTexCoord2d(1,1); }  glVertex3d(x + sizex,    y + sizey,     z + sizez);
    glEnd();

    if (tex != 0) { glBindTexture(GL_TEXTURE_2D, tex); }
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);
    if (tex == 0) { glColor4f((double)(color.getR() / 255.0), (double)(color.getG() / 255.0), (double)(color.getB() / 255.0), (double)(color.getA() / 255.0)); }
    if (tex != 0) { glTexCoord2d(0,1); }  glVertex3d(x,            y,              z + sizez);
    if (tex != 0) { glTexCoord2d(0,0); }  glVertex3d(x,            y,              z);
    if (tex != 0) { glTexCoord2d(1,0); }  glVertex3d(x + sizex,    y,              z);
    if (tex != 0) { glTexCoord2d(1,1); }  glVertex3d(x + sizex,    y,              z + sizez);
    glEnd();

    if (tex != 0) { glBindTexture(GL_TEXTURE_2D, tex); }
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    if (tex == 0) { glColor4f((double)(color.getR() / 255.0), (double)(color.getG() / 255.0), (double)(color.getB() / 255.0), (double)(color.getA() / 255.0)); }
    if (tex != 0) { glTexCoord2d(0,1); }  glVertex3d( x,           y + sizey,      z + sizez);
    if (tex != 0) { glTexCoord2d(0,0); }  glVertex3d( x,           y + sizey,      z);
    if (tex != 0) { glTexCoord2d(1,0); }  glVertex3d( x,           y,              z);
    if (tex != 0) { glTexCoord2d(1,1); }  glVertex3d( x,           y,              z + sizez);
    glEnd();

    if (tex != 0) { glBindTexture(GL_TEXTURE_2D, tex); }
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, -1.0f);
    if (tex == 0) { glColor4f((double)(color.getR() / 255.0), (double)(color.getG() / 255.0), (double)(color.getB() / 255.0), (double)(color.getA() / 255.0)); }
    if (tex != 0) { glTexCoord2d(0,1); }  glVertex3d(x + sizex,     y + sizey, z);
    if (tex != 0) { glTexCoord2d(0,0); }  glVertex3d(x + sizex,     y, z);
    if (tex != 0) { glTexCoord2d(1,0); }  glVertex3d(x,             y, z);
    if (tex != 0) { glTexCoord2d(1,1); }  glVertex3d(x,             y + sizey, z);
    glEnd();

    if (tex != 0) { glBindTexture(GL_TEXTURE_2D, tex); }
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    if (tex == 0) { glColor4f((double)(color.getR() / 255.0), (double)(color.getG() / 255.0), (double)(color.getB() / 255.0), (double)(color.getA() / 255.0)); }
    if (tex != 0) { glTexCoord2d(0,1); }  glVertex3d(x + sizex,     y, z + sizez);
    if (tex != 0) { glTexCoord2d(0,0); }  glVertex3d(x + sizex,     y + sizey, z + sizez);
    if (tex != 0) { glTexCoord2d(1,0); }  glVertex3d(x,             y + sizey, z + sizez);
    if (tex != 0) { glTexCoord2d(1,1); }  glVertex3d(x,             y, z + sizez);
    glEnd();

    glColor4f(1,1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}
