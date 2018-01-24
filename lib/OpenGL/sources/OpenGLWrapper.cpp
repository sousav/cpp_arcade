//
// OpenGLWrapper.cpp for  in /home/gambin_l/Shared/cpp_arcade/lib/OpenGL
//
// Made by lucas gambini
// Login   <gambin_l@epitech.net>
//
// Started on  Thu Mar 16 19:09:58 2017 lucas gambini
// Last update Sun Apr  9 22:08:45 2017 Gaëtan Léandre
//

#include "OpenGLWrapper.hpp"

//OpenGLWrapper * OpenGLWrapper::static_this = NULL;
OpenGLWrapper::OpenGLWrapper() {
    #ifdef __APPLE__
        this->_width = 1200;
        this->_height = 1200;
    #else
        this->_width = 800;
        this->_width = 800;
    #endif
    this->_libName = "OpenGL";
    //this->static_this = this;
    for (int i = 0; i < 1024; i++) {
        this->_key[i] = 0;
        this->_released_key[i] = 0;
    }
}

OpenGLWrapper::~OpenGLWrapper() {
    //OpenGLWrapper::static_this = NULL;
    glfwDestroyWindow(_window);
    glfwTerminate();
    GLTextureLoader::clean();
    GLObjectLoader::clean();
    GLSound::clean();
}

void OpenGLWrapper::InitLib() {
    // Initialise GLFW
    if (!glfwInit()){
        std::cout << "Erreur d'initialisation de glfwInit" << std::endl;
        throw NoGraphServerFound("No graphical server found");
    }

    glfwWindowHint(GLFW_SAMPLES, 4);

    this->_window = glfwCreateWindow(this->_width, this->_height, this->_libName.data(), NULL, NULL);
    if (!this->_window) {
        std::cout << "Erreur d'initialisation de glfwCreateWindow" << std::endl;
        glfwTerminate();
        throw GraphServerFailed("Your graphical server failed opening a window");
    }

    glfwMakeContextCurrent(this->_window);

	// Initialize GLEW
    #ifdef __APPLE__
    glewExperimental = GL_TRUE;
    #endif
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cout << "Erreur d'initialisation de glewInit" << std::endl;
        glfwTerminate();
        throw GraphServerFailed("Your graphical server failed setting up the window");
    }

    glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);

    glShadeModel(GL_SMOOTH);
	glClearColor(0.075f, 0.075f, 0.075f, 0.5f);
	glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);

    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 0.0, 0.0, 35.0, 25.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, this->_width, this->_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, (double)(this->_width / this->_height), 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OpenGLWrapper::giveData(std::vector <AData *> const &datas) {
    glfwWindowShouldClose(this->_window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLCamera glCamera(datas);
    glCamera.setupView();

    for (auto const & data: datas) {
        handleData(*data);
    }

    glfwPollEvents();
    if (handleEvent(_window, 0, 0, 0, 0) == 1)
        return;
    glfwSwapBuffers(this->_window);
}

void OpenGLWrapper::giveSprite(std::vector <std::string> const &spriteList) {
    for (auto const & sprite: spriteList) {
        GLTextureLoader::load(sprite);
    }
}

void OpenGLWrapper::giveMusic(std::vector <std::string> const &musicList)
{
    for (auto const & music: musicList) {
        sf::SoundBuffer *buffer = new sf::SoundBuffer();
        buffer->loadFromFile(music);
        GLSound::_soundBufferMap[music] = buffer;
    }
}

void OpenGLWrapper::giveModel3D(std::vector <std::string> const &modelList)
{
    for (auto const & model: modelList) {
        GLObjectLoader::load(model);
    }
}


void OpenGLWrapper::setBridge(IArcadeBridge * bridge) {
    this->_bridge = bridge;
}


void OpenGLWrapper::handleData(AData const & data) {
    switch (data.getShape()) {
        case DataType::Sphere:
            this->handleSphere(data);
            break;
        case DataType::Cube:
            this->handleCube(data);
            break;
        case DataType::Light:
            this->handleLight(data);
            break;
        case DataType::Music:
            this->handleMusic(data);
            break;
        case DataType::Text:
            this->handleText(data);
            break;
        default:
            break;
    }
}

void OpenGLWrapper::handleSphere(AData const & data) {
    try
    {
        Sphere const & sphere = dynamic_cast<Sphere const &>(data);
        if (sphere.getTexture().getModel().getObject() == "") {
            GLSphere glSphere(sphere);
            glSphere.draw();
        } else {
            GLObject obj(sphere.getTexture().getModel().getObject());
            obj.setOffset(sphere.getRadius(), sphere.getRadius(), sphere.getRadius());
            obj.move(sphere.getTexture().getModel().getPosition().getX() + sphere.getPosition().getX(),
                     sphere.getTexture().getModel().getPosition().getY() + sphere.getPosition().getY(),
                     sphere.getTexture().getModel().getPosition().getZ() + sphere.getPosition().getZ());
            obj.scale(sphere.getTexture().getModel().getScale().getX(),
                      sphere.getTexture().getModel().getScale().getY(),
                      sphere.getTexture().getModel().getScale().getZ());
            obj.rotate(sphere.getTexture().getModel().getRotation().getX(),
                       sphere.getTexture().getModel().getRotation().getY() + sphere.getTexture().getRotation(),
                       sphere.getTexture().getModel().getRotation().getZ());
            obj.draw();
        }
    } catch (std::exception const &e){
        std::cerr << e.what() << std::endl;
    }
}

void OpenGLWrapper::handleCube(AData const & data) {
    try
    {
        Cube const & cube = dynamic_cast<Cube const &>(data);
        if (cube.getTexture().getModel().getObject() == "") {
            GLCube glCube(cube);
            glCube.draw();
        } else {
            GLObject obj(cube.getTexture().getModel().getObject());
            obj.setOffset(cube.getSize().getX() / 2, cube.getSize().getY() / 2, cube.getSize().getZ() / 2);
            obj.move(cube.getTexture().getModel().getPosition().getX() + cube.getPosition().getX(),
                     cube.getTexture().getModel().getPosition().getY() + cube.getPosition().getY(),
                     cube.getTexture().getModel().getPosition().getZ() + cube.getPosition().getZ());
            obj.scale(cube.getTexture().getModel().getScale().getX(),
                      cube.getTexture().getModel().getScale().getY(),
                      cube.getTexture().getModel().getScale().getZ());
            obj.rotate(cube.getTexture().getModel().getRotation().getX(),
                       cube.getTexture().getModel().getRotation().getY() + cube.getTexture().getRotation(),
                       cube.getTexture().getModel().getRotation().getZ());
            obj.draw();
        }
    } catch (std::exception const &e){
        std::cerr << e.what() << std::endl;
    }
}

void OpenGLWrapper::handleCamera(AData const & data) {
    (void)data;
}

void OpenGLWrapper::handleLight(AData const & data) {
    (void)data;
}

void OpenGLWrapper::handleMusic(AData const & data) {
    try
    {
        Audio const & audio = dynamic_cast<Audio const &>(data);
        GLSound sound(audio);
        sound.play();
    } catch (std::exception const &e){
        std::cerr << e.what() << std::endl;
    }
}

void OpenGLWrapper::handleText(AData const & data) {
    try
    {
        Text const &texte = dynamic_cast<Text const &>(data);
        GLText text(texte);
        text.setWindow(this->_window);
        text.draw();
    } catch (std::exception const &e){
        std::cerr << e.what() << std::endl;
    }
}

// void OpenGLWrapper::handleEventStatic(GLFWwindow* window, int key, int scancode, int action, int mods)
// {
//     if (OpenGLWrapper::static_this != NULL)
//         OpenGLWrapper::static_this->handleEvent(window, key, scancode, action, mods);
// }
int OpenGLWrapper::handleEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
    (void)window;
    (void)scancode;
    (void)mods;
    (void)key;
    (void)action;
    for (int i = 0; i < 512; i++) {
        int tmp = glfwGetKey(window, i);
        if (tmp == GLFW_RELEASE && this->_key[i] == GLFW_PRESS)
            this->_released_key[i] = 1;
        this->_key[i] = tmp;
    }

    if (this->_released_key[GLFW_KEY_LEFT]) {
        this->goRight();
        this->_released_key[GLFW_KEY_LEFT] = 0;
    }

    if (this->_released_key[GLFW_KEY_RIGHT]) {
        this->goLeft();
        this->_released_key[GLFW_KEY_RIGHT] = 0;
    }

    if (this->_released_key[GLFW_KEY_UP]) {
        this->goUp();
        this->_released_key[GLFW_KEY_UP] = 0;
    }

    if (this->_released_key[GLFW_KEY_DOWN]) {
        this->goDown();
        this->_released_key[GLFW_KEY_DOWN] = 0;
    }

    if (this->_released_key[GLFW_KEY_SPACE]) {
        this->shoot();
        this->_released_key[GLFW_KEY_SPACE] = 0;
    }

    if (this->_released_key[GLFW_KEY_2]) {
        this->prevGraph();
        return 1;
        this->_released_key[GLFW_KEY_2] = 0;
    }

    if (this->_released_key[GLFW_KEY_3]) {
        this->nextGraph();
        return 1;
        this->_released_key[GLFW_KEY_3] = 0;
    }

    if (this->_released_key[GLFW_KEY_4]) {
        this->prevGame();
        this->_released_key[GLFW_KEY_4] = 0;
    }

    if (this->_released_key[GLFW_KEY_5]) {
        this->nextGame();
        this->_released_key[GLFW_KEY_5] = 0;
    }

    if (this->_released_key[GLFW_KEY_8]) {
        this->pressEight();
        this->_released_key[GLFW_KEY_8] = 0;
    }

    if (this->_released_key[GLFW_KEY_9]) {
        this->pressNine();
        this->_released_key[GLFW_KEY_9] = 0;
    }

    if (this->_released_key[GLFW_KEY_ENTER]) {
        this->goForward();
        this->_released_key[GLFW_KEY_ENTER] = 0;
    }

    if (this->_released_key[GLFW_KEY_ESCAPE]) {
        this->pressEchap();
        this->_released_key[GLFW_KEY_ESCAPE] = 0;
    }
    return 0;
}


void OpenGLWrapper::toggleRunning() const {
    this->_bridge->toggleRunning();
}

void OpenGLWrapper::prevGraph() const {
    this->_bridge->prevGraph();
}

void OpenGLWrapper::nextGraph() const {
    this->_bridge->nextGraph();
}

void OpenGLWrapper::prevGame() const {
    this->_bridge->prevGame();
}

void OpenGLWrapper::nextGame() const {
    this->_bridge->nextGame();
}

void OpenGLWrapper::goUp() const {
    this->_bridge->goUp();
}

void OpenGLWrapper::goDown() const {
    this->_bridge->goDown();
}

void OpenGLWrapper::goLeft() const {
    this->_bridge->goLeft();
}

void OpenGLWrapper::goRight() const {
    this->_bridge->goRight();
}

void OpenGLWrapper::goForward() const {
    this->_bridge->goForward();
}

void OpenGLWrapper::shoot() const {
    this->_bridge->shoot();
}

void OpenGLWrapper::pressEchap() const {
    this->_bridge->pressEchap();
}

void OpenGLWrapper::pressEight() const {
    this->_bridge->pressEight();
}

void OpenGLWrapper::pressNine() const {
    this->_bridge->pressNine();
}

std::string const & OpenGLWrapper::getLibName() const {
    return this->_libName;
}

extern "C" {

    IGraph *Create() {
        std::cout << "Created Lib OpenGL" << std::endl;
        return new OpenGLWrapper();
    }

}
