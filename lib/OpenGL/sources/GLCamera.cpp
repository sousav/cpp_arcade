//
// GLCamera.cpp for  in /Users/vicostudio/Documents/Shared Folder/TEK2/CPP/cpp_arcade/lib/OpenGL/sources/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sun Mar 26 01:06:36 2017 Sousa Victor
// Last update Fri Apr  7 19:24:16 2017 Sousa Victor
//

#include "GLCamera.hpp"

GLCamera::GLCamera() : _camera(Position()){
    this->_hasCamera = false;
}

GLCamera::GLCamera(Camera const &camera): _camera(camera) {
    this->_hasCamera = true;
}

GLCamera::GLCamera(std::vector <AData *> const &datas): _camera(Position()) {
    for (auto const & data: datas) {
        if (data->getShape() == DataType::Camera) {
            this->_camera = *dynamic_cast<Camera *>(data);
            this->_hasCamera = true;
            return;
        }
    }
    this->_hasCamera = false;
}

GLCamera::~GLCamera() {

}

GLCamera &GLCamera::operator=(const GLCamera &obj) {
    this->_camera = obj._camera;
    this->_hasCamera = obj._hasCamera;
    return *this;
}

GLCamera::GLCamera(GLCamera const &obj): _camera(obj._camera) {
    this->_hasCamera = obj._hasCamera;
}

void GLCamera::setupView() const {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (!this->_hasCamera) {
        gluLookAt(50, 50, 65, 50, 50, 0, 0, 1, 0);
        return;
    }

    glRotatef(_camera.getIncY(), 1.0f, 0.0f, 0.0f); // Rotate our camera on the x-axis (looking up and down)
	glRotatef(_camera.getIncX(), 0.0f, 0.0f, 1.0f); // Rotate our camera on the  y-axis (looking left and right)

	// Translate the ModelView matrix to the position of our camera - everything should now be drawn relative
	// to this position!
	glTranslatef( -_camera.getPosition().getX(), -_camera.getPosition().getY(), -_camera.getPosition().getZ());

}
