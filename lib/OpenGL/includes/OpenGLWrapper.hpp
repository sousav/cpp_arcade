//
// OpenGLWrapper.hpp for  in /home/gambin_l/Shared/cpp_arcade/lib/OpenGL
//
// Made by lucas gambini
// Login   <gambin_l@epitech.net>
//
// Started on  Thu Mar 16 19:10:10 2017 lucas gambini
// Last update Sun Apr  9 21:27:48 2017 Gaëtan Léandre
//

#ifndef OPENGLWRAPPER_HPP_
#define OPENGLWRAPPER_HPP_

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
#include <glm/gtx/rotate_vector.hpp>
#include <SFML/Graphics.hpp>

#include "Exceptions.hpp"
#include "IGraph.hpp"
#include "GLSphere.hpp"
#include "GLCube.hpp"
#include "GLCamera.hpp"
#include "GLTextureLoader.hpp"
#include "GLText.hpp"
#include "GLSound.hpp"
#include "GLObject.hpp"

class OpenGLWrapper : public IGraph  {

protected:
	//static OpenGLWrapper *static_this;

public:
    OpenGLWrapper();
    ~OpenGLWrapper();

    void InitLib();
    void setBridge(IArcadeBridge * bridge);
    void giveData(std::vector <AData *> const &data);
    void giveSprite(std::vector <std::string> const &spriteList);
    void giveMusic(std::vector <std::string> const &musicList);
    void giveModel3D(std::vector <std::string> const &modelList);

    void handleData(AData const & data);
    void handleSphere(AData const & data);
    void handleCube(AData const & data);
    void handleCamera(AData const & data);
    void handleLight(AData const & data);
    void handleMusic(AData const & data);
    void handleText(AData const & data);

    std::string const & getLibName() const;

private:
    std::string _libName;
    IArcadeBridge *_bridge;
    GLFWwindow* _window;

    int handleEvent(GLFWwindow* window, int key, int scancode, int action, int mods);

    void toggleRunning() const;
    void prevGraph() const;
    void nextGraph() const;
    void prevGame() const;
    void nextGame() const;
    void goUp() const;
    void goDown() const;
    void goLeft() const;
    void goRight() const;
    void goForward() const;
    void shoot() const;
    void pressEchap() const;
    void pressEight() const;
    void pressNine() const;

    unsigned int _width;
    unsigned int _height;

    int _key[1024];
    int _released_key[1024];

};

#else

class OpenGLWrapper;

#endif /*OPENGLWRAPPER_HPP_*/
