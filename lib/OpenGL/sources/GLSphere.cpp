//
// GLSphere.cpp for  in /Users/vicostudio/Documents/Shared Folder/TEK2/CPP/cpp_arcade/lib/OpenGL/sources/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Fri Mar 31 00:39:50 2017 Sousa Victor
// Last update Sun Apr  9 03:24:31 2017 Sousa Victor
//

#include "GLSphere.hpp"

GLSphere::GLSphere(Sphere const &sphere) {
    this->_radius = sphere.getRadius();
    this->_pos = sphere.getPosition();
    this->_texture = sphere.getTexture();
    unsigned int rings = 16;
    unsigned int sectors = 16;
    float const R = 1./(float)(rings-1);
    float const S = 1./(float)(sectors-1);
    unsigned int r, s;

    this->_vertices.resize(rings * sectors * 3);
    this->_normals.resize(rings * sectors * 3);
    this->_texcoords.resize(rings * sectors * 2);
    std::vector<GLfloat>::iterator v = this->_vertices.begin();
    std::vector<GLfloat>::iterator n = this->_normals.begin();
    std::vector<GLfloat>::iterator t = this->_texcoords.begin();
    for(r = 0; r < rings; r++) for(s = 0; s < sectors; s++) {
        float const y = sin( -M_PI_2 + M_PI * r * R );
        float const x = cos(2*M_PI * s * S) * sin( M_PI * r * R );
        float const z = sin(2*M_PI * s * S) * sin( M_PI * r * R );

        *t++ = s*S;
        *t++ = r*R;

        *v++ = x * _radius * 1.35;
        *v++ = y * _radius * 1.35;
        *v++ = z * _radius * 1.35;

        *n++ = x;
        *n++ = y;
        *n++ = z;
    }

    this->_indices.resize(rings * sectors * 4);
    std::vector<GLushort>::iterator i = this->_indices.begin();
    for(r = 0; r < rings-1; r++) for(s = 0; s < sectors-1; s++) {
            *i++ = r * sectors + s;
            *i++ = r * sectors + (s+1);
            *i++ = (r+1) * sectors + (s+1);
            *i++ = (r+1) * sectors + s;
    }
}

GLSphere::~GLSphere() {

}

GLSphere &GLSphere::operator=(const GLSphere &obj) {
    this->_radius = obj._radius;
    this->_pos = obj._pos;
    this->_texture = obj._texture;
    this->_vertices = obj._vertices;
    this->_normals = obj._normals;
    this->_texcoords = obj._texcoords;
    this->_indices = obj._indices;
    return *this;
}

GLSphere::GLSphere(GLSphere const &obj) {
    this->_radius = obj._radius;
    this->_pos = obj._pos;
    this->_texture = obj._texture;
    this->_vertices = obj._vertices;
    this->_normals = obj._normals;
    this->_texcoords = obj._texcoords;
    this->_indices = obj._indices;
}


void GLSphere::draw() {
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    GLuint tex = GLTextureLoader::load(this->_texture.getSprite());
    if (tex != 0) {
        glEnable(GL_TEXTURE_2D);
    } else {
        glDisable(GL_TEXTURE_2D);
    }
    if (tex != 0) {
        glBindTexture(GL_TEXTURE_2D, tex);
    } else if (tex == 0) {
        glColor4f((double)(this->_texture.getColor().getR() / 255.0),
                (double)(this->_texture.getColor().getG() / 255.0),
                (double)(this->_texture.getColor().getB() / 255.0),
                (double)(this->_texture.getColor().getA() / 255.0));
    }
    glTranslatef(this->_pos.getX() + this->_radius * 1.35, this->_pos.getY() + this->_radius * 1.35, this->_pos.getZ() + this->_radius * 1.35);
    glRotatef(this->_texture.getRotation(), 0, 0, 1);
    glRotatef(90, 0, 1, 0);
    glRotatef(180, 1, 0, 0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, &this->_vertices[0]);
    glNormalPointer(GL_FLOAT, 0, &this->_normals[0]);
    glTexCoordPointer(2, GL_FLOAT, 0, &this->_texcoords[0]);
    glDrawElements(GL_QUADS, this->_indices.size(), GL_UNSIGNED_SHORT, &this->_indices[0]);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}
