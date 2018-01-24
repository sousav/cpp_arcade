//
// SFMLWrapper.cpp for  in /home/gambin_l/Shared/cpp_arcade/Graphics/SFML
//
// Made by lucas gambini
// Login   <gambin_l@epitech.net>
//
// Started on  Thu Mar 16 17:44:08 2017 lucas gambini
// Last update Sun Apr  9 22:03:12 2017 Gaëtan Léandre
//

#include "IGraph.hpp"
#include "SFMLWrapper.hpp"

SFMLWrapper::SFMLWrapper() {
    #ifdef __APPLE__
        this->_width = 1200;
        this->_height = 1200;
    #else
        this->_width = 800;
        this->_width = 800;
    #endif
    this->_libName = std::string("lib_arcade_sfml.so");
}

SFMLWrapper::~SFMLWrapper() {
    this->_window->close();
    delete this->_window;
    for(std::map<std::string, sf::Texture *>::iterator it=this->_spriteMap.begin() ; it != this->_spriteMap.end(); it++ ) {
        delete (it->second);
    }
    for(std::vector<sf::Sound *>::iterator it=this->_soundList.begin() ; it < this->_soundList.end(); it++ ) {
        (*(it))->stop();
        delete (*it);
    }
    for(std::map<std::string, sf::SoundBuffer *>::iterator it=this->_soundBufferMap.begin() ; it != this->_soundBufferMap.end(); it++ ) {
        delete (it->second);
    }
    delete this->_font;
}

void SFMLWrapper::InitLib() {
    this->_window = new sf::RenderWindow(sf::VideoMode(this->_width, this->_height), "My window");
    if (this->_window == NULL)
        throw NoGraphServerFound("No graphical server found");
    this->_font = new sf::Font();
    this->_font->loadFromFile("./Assets/Fonts/ARCADEPI.TTF");
}

std::string const & SFMLWrapper::getLibName() const {
    return this->_libName;
}

void SFMLWrapper::giveData(std::vector <AData *> const &datas) {
    this->_window->isOpen();
    sf::Event event;
    while (this->_window->pollEvent(event))
    {
        if (this->handleEvent(event)) {
            return;
        }
    }
    this->_window->clear(sf::Color::White);
    for(auto const& data: datas) {
        this->handleData(*data);
    }
    this->_window->display();
}

void SFMLWrapper::giveSprite(std::vector <std::string> const &spriteList) {
    for (auto const &sprite: spriteList) {
        sf::Texture *texture = new sf::Texture();
        texture->loadFromFile(sprite);
        this->_spriteMap[sprite] = texture;
    }
}

void SFMLWrapper::giveMusic(std::vector <std::string> const &musicList)
{
    for (auto const &music: musicList) {
        std::cout << "loading: " << music << std::endl;
        sf::SoundBuffer *buffer = new sf::SoundBuffer();
        buffer->loadFromFile(music);
        this->_soundBufferMap[music] = buffer;
    }
}

void SFMLWrapper::giveModel3D(std::vector <std::string> const &modelList)
{
    (void)modelList;
}

void SFMLWrapper::setBridge(IArcadeBridge * bridge) {
    this->_bridge = bridge;
}

int SFMLWrapper::handleEvent(sf::Event const & event) {
    switch (event.type)
    {
        // window closed
        case sf::Event::Closed:
            this->_window->close();
            break;

        // key pressed
        case sf::Event::KeyPressed:
            switch (event.key.code) {
                case sf::Keyboard::Left:
                    this->goLeft();
                    break;
                case sf::Keyboard::Right:
                    this->goRight();
                    break;
                case sf::Keyboard::Up:
                    this->goUp();
                    break;
                case sf::Keyboard::Down:
                    this->goDown();
                    break;
                case sf::Keyboard::Num2:
                    this->prevGraph();
                    return (1);
                case sf::Keyboard::Num3:
                    this->nextGraph();
                    return (1);
                case sf::Keyboard::Num4:
                    this->prevGame();
                    return (1);
                case sf::Keyboard::Num5:
                    this->nextGame();
                    return (1);
                case sf::Keyboard::Num8:
                    this->pressEight();
                    return (1);
                case sf::Keyboard::Num9:
                    this->pressNine();
                    return (1);
                case sf::Keyboard::Escape:
                    this->pressEchap();
                    return (1);
                case sf::Keyboard::Space:
                    this->shoot();
                    break;
                case sf::Keyboard::Return:
                    this->goForward();
                    break;
                default:
                    break;
            }
            break;

        // we don't process other types of events
        default:
            break;
    }
    return 0;
}

void SFMLWrapper::handleData(AData const & data) {
    switch (data.getShape()) {
        case DataType::Sphere:
            this->handleSphere(data);
            break;
        case DataType::Cube:
            this->handleCube(data);
            break;
        case DataType::Camera:
            this->handleCamera(data);
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
    }
}

void SFMLWrapper::handleSphere(AData const & data) {
    try
    {
        Sphere const & sphere = dynamic_cast<Sphere const &>(data);
        sf::CircleShape circle;
        circle.setRadius((sphere.getRadius() / 100.0) * this->_width);
        circle.setPosition((sphere.getPosition().getX() / 100.0) * this->_width, (sphere.getPosition().getY() / 100.0) * this->_height);
        if (sphere.getTexture().getSprite() == "") {
            Color const & color = sphere.getTexture().getColor();
            circle.setFillColor(sf::Color(color.getR(), color.getG(), color.getB(), color.getA()));
        } else {
            std::map<std::string, sf::Texture *>::iterator it = this->_spriteMap.find(sphere.getTexture().getSprite());
            if (it != this->_spriteMap.end()) {
                circle.setTexture(it->second);
            } else {
                std::cout << "loading: " << sphere.getTexture().getSprite() << std::endl;
                sf::Texture *texture = new sf::Texture();
                texture->loadFromFile(sphere.getTexture().getSprite());
                this->_spriteMap[sphere.getTexture().getSprite()] = texture;
                circle.setTexture(texture);
            }
        }
        circle.setOrigin(circle.getRadius(), circle.getRadius());
        circle.setRotation(sphere.getTexture().getRotation());
        circle.setPosition(circle.getPosition().x + circle.getOrigin().x, circle.getPosition().y + circle.getOrigin().y);
        this->_window->draw(circle);
    } catch (std::exception const &e){
        std::cerr << e.what() << std::endl;
    }
}

void SFMLWrapper::handleCube(AData const & data) {
    try
    {
        Cube const & cube = dynamic_cast<Cube const &>(data);
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f((cube.getSize().getX() / 100.0) * this->_width, (cube.getSize().getY() / 100.0) * this->_height));
        rectangle.setPosition((cube.getPosition().getX() / 100.0) * this->_width, (cube.getPosition().getY() / 100.0) * this->_height);
        if (cube.getTexture().getSprite() == "") {
            Color const & color = cube.getTexture().getColor();
            rectangle.setFillColor(sf::Color(color.getR(), color.getG(), color.getB(), color.getA()));
        } else {
            std::map<std::string, sf::Texture *>::iterator it = this->_spriteMap.find(cube.getTexture().getSprite());
            if (it != this->_spriteMap.end()) {
                rectangle.setTexture(it->second);
            } else {
                std::cout << "loading: " << cube.getTexture().getSprite() << std::endl;
                sf::Texture *texture = new sf::Texture();
                texture->loadFromFile(cube.getTexture().getSprite());
                this->_spriteMap[cube.getTexture().getSprite()] = texture;
                rectangle.setTexture(texture);
            }
        }
        rectangle.setOrigin(rectangle.getSize().x * 0.5f, rectangle.getSize().y * 0.5f);
        rectangle.setRotation(cube.getTexture().getRotation());
        rectangle.setPosition(rectangle.getPosition().x + rectangle.getOrigin().x, rectangle.getPosition().y + rectangle.getOrigin().y);
        this->_window->draw(rectangle);
    } catch (std::exception const &e){
        std::cerr << e.what() << std::endl;
    }
}

void SFMLWrapper::handleCamera(AData const & data) {
    (void)data;
}

void SFMLWrapper::handleLight(AData const & data) {
    (void)data;
}

void SFMLWrapper::handleMusic(AData const & data) {
    try
    {
        Audio const & audio = dynamic_cast<Audio const &>(data);
        std::map<std::string, sf::SoundBuffer *>::iterator it = this->_soundBufferMap.find(audio.getAudio());
        if (it != this->_soundBufferMap.end()) {
            sf::Sound *sound = new sf::Sound();
            sound->setBuffer(*it->second);
            sound->setVolume(audio.getIntensity());
            this->_soundList.push_back(sound);
            sound->play();
        } else {
            std::cout << "loading: " << audio.getAudio() << std::endl;
            sf::SoundBuffer *buffer = new sf::SoundBuffer();
            buffer->loadFromFile(audio.getAudio());
            this->_soundBufferMap[audio.getAudio()] = buffer;
            sf::Sound *sound = new sf::Sound();
            sound->setBuffer(*buffer);
            this->_soundList.push_back(sound);
            sound->play();
        }
    } catch (std::exception const &e){
        std::cerr << e.what() << std::endl;
    }
}

void SFMLWrapper::handleText(AData const & data) {
    try
    {
        Text const & text = dynamic_cast<Text const &>(data);
        sf::Text texte;
        texte.setFont(*this->_font);
        texte.setString(text.getText());
        texte.setCharacterSize(text.getSize());
        Color const & color = text.getTexture().getColor();
        #ifdef __APPLE__
        texte.setFillColor(sf::Color(color.getR(), color.getG(), color.getB(), color.getA()));
        #else
        texte.setColor(sf::Color(color.getR(), color.getG(), color.getB(), color.getA()));
        #endif
        texte.setStyle(sf::Text::Bold);
        if (text.getAlign() == Text::Align::LEFT)
            texte.setPosition((text.getPosition().getX() / 100.0) * this->_width, (text.getPosition().getY() / 100.0) * this->_height);
        else if (text.getAlign() == Text::Align::CENTER) {
            sf::FloatRect textRect = texte.getLocalBounds();
            texte.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top  + textRect.height / 2.0f);
            texte.setPosition((text.getPosition().getX() / 100.0) * this->_width, (text.getPosition().getY() / 100.0) * this->_height);
        } else {
            sf::FloatRect textRect = texte.getLocalBounds();
            texte.setOrigin(textRect.left + textRect.width, textRect.top  + textRect.height);
            texte.setPosition((text.getPosition().getX() / 100.0) * this->_width, (text.getPosition().getY() / 100.0) * this->_height);
        }
        this->_window->draw(texte);
    } catch (std::exception const &e){
        std::cerr << e.what() << std::endl;
    }
}


void SFMLWrapper::toggleRunning() const {

}

void SFMLWrapper::prevGraph() const {
    this->_bridge->prevGraph();
}

void SFMLWrapper::nextGraph() const {
    this->_bridge->nextGraph();
}

void SFMLWrapper::prevGame() const {
    this->_bridge->prevGame();
}

void SFMLWrapper::nextGame() const {
    this->_bridge->nextGame();
}

void SFMLWrapper::goUp() const {
    this->_bridge->goUp();
}

void SFMLWrapper::goDown() const {
    this->_bridge->goDown();
}

void SFMLWrapper::goLeft() const {
    this->_bridge->goLeft();
}

void SFMLWrapper::goRight() const {
    this->_bridge->goRight();
}

void SFMLWrapper::goForward() const {
    this->_bridge->goForward();
}

void SFMLWrapper::shoot() const {
    this->_bridge->shoot();
}

void SFMLWrapper::pressEchap() const {
    this->_bridge->pressEchap();
}

void SFMLWrapper::pressEight() const {
    this->_bridge->pressEight();
}

void SFMLWrapper::pressNine() const {
    this->_bridge->pressNine();
}

extern "C" {

    IGraph *Create() {
        std::cout << "Created Lib SFML" << std::endl;
        return (new SFMLWrapper());
    }

}
