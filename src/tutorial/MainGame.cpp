#include "MainGame.h"
#include <OpenGL/gl3.h>

#include <iostream>
#include "ModelTexture.h"
#include "OBJLoader.h"

#include "config.h"

MainGame::MainGame() {
    _gameState = GameState::PLAY;
     
    _windowSizeX = 2048;
    _windowSizeY = 1536;
}

MainGame::~MainGame() {
    if(_window.isOpen())
        _window.close();
}

void MainGame::run() {
    initSystems();
    
    gameLoop();
}
  
void MainGame::initSystems() {
    // Window
    sf::ContextSettings requestedSettings;
    requestedSettings.depthBits = 24;
    requestedSettings.stencilBits = 8;
    requestedSettings.antialiasingLevel = 4;
    requestedSettings.majorVersion = 3;
    requestedSettings.minorVersion = 2;
    
    _window.create(sf::VideoMode(_windowSizeX, _windowSizeY), "Game Engine", sf::Style::Default, requestedSettings);
    _window.setVerticalSyncEnabled(true);

    // activate the window
    _window.setActive(true);
    
    sf::ContextSettings realSettings = _window.getSettings();

    std::cout << "depth bits:" << realSettings.depthBits << std::endl;
    std::cout << "stencil bits:" << realSettings.stencilBits << std::endl;
    std::cout << "antialiasing level:" << realSettings.antialiasingLevel << std::endl;
    std::cout << "version:" << realSettings.majorVersion << "." << realSettings.minorVersion << std::endl;
    
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version supported: " << glGetString(GL_VERSION) << std::endl;
    
    // Prepare OpenGL
    glEnable(GL_TEXTURE_2D);
    std::string modelPath = graphy_RESOURCE_PATH;
    modelPath += "/resources/dragon.obj";
    std::string texturePath = graphy_RESOURCE_PATH;
    texturePath += "/resources/cube.png";

    RawModel_ptr rModel = OBJLoader::loadObjModel(modelPath, _loader);
    ModelTexture_ptr texture = _loader.loadTexture(texturePath);
    texture->setShineDamper(10);
    texture->setReflectivity(1);
    TexturedModel_ptr tModel = std::make_shared<TexturedModel>(rModel, texture);
    
    _entity = std::make_shared<Entity>(tModel, glm::vec3(0, 0, -25), glm::vec3(0, 0, 0), 1.0f);
    
    _shader = std::make_shared<StaticShader>();
    _shader->init();
    
    _renderer = std::make_shared<Renderer>((float)_windowSizeY/(float)_windowSizeX, 
                                           _shader->getProjectionMatrixLocation(),
                                           _shader);
    
    _camera = std::make_shared<Camera>();
    _light = std::make_shared<Light>(glm::vec3(0,4,-20), glm::vec3(1, .9, .9));
    
    // Main View
    float y_ratio = (_windowSizeY - 50) / _windowSizeY;
    _gameView.setSize(sf::Vector2f(_windowSizeX, _windowSizeY - 50));
    _gameView.setCenter(sf::Vector2f(0, 0));
    _gameView.setViewport(sf::FloatRect(0, 0, 1, y_ratio));

    // Status Bar View
    _statusBarView.setSize(sf::Vector2f(_windowSizeX, 50));
    _statusBarView.setCenter(sf::Vector2f(_windowSizeX / 2, 25));
    _statusBarView.setViewport(sf::FloatRect(0, y_ratio, 1, 1.0 - y_ratio));
    
    // Font
    std::string fontPath = graphy_RESOURCE_PATH;
    fontPath += "/resources/Verdana.ttf";

    if(!_font.loadFromFile(fontPath)) {
        std::cout << "Error loading font" << std::endl;
        exit(-1);
		}
		
		// Text
		_text.setFont(_font);
		_text.setCharacterSize(24);
		_text.setFillColor(sf::Color::White);
}

void MainGame::gameLoop() {

    // Perform OpenGL initializations
	glMatrixMode(GL_PROJECTION);

    while(_gameState != GameState::EXIT) {
        processInput();
        
        // Game Logic
        //_entity->increasePosition(0, 0, -0.001);
        _entity->increaseRotation(0.001, .005, 0);

        // SFML... Activate the window
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        _window.clear(sf::Color::Black);
        _window.setActive(true);
        _window.popGLStates();

        // Prep...
        _renderer->prepare();
        _shader->start();
        _shader->loadViewMatrix(_camera);
        _shader->loadLight(_light);

        // Draw...
        _renderer->render(_entity, _shader);
        _shader->stop();

        // SFML... Draw and Deactivate
        _window.pushGLStates();
        _window.display();
        _window.setActive(false);
    }
}

void MainGame::processInput() {
    sf::Event event;
    while (_window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            _gameState = GameState::EXIT;
        case sf::Event::KeyPressed:
            if(event.key.code == sf::Keyboard::W) {
              _camera->increasePosition(0, 0, -0.02f);
            } else if(event.key.code == sf::Keyboard::S) {
              _camera->increasePosition(0, 0, 0.02f);
            } else if(event.key.code == sf::Keyboard::D) {
              _camera->increasePosition(0.02f, 0, 0);
            } else if(event.key.code == sf::Keyboard::A) {
              _camera->increasePosition(-0.02f, 0, 0);
            }
            break;
        case sf::Event::Resized:
            // adjust the viewport when the window is resized
            glViewport(0, 0, event.size.width, event.size.height);
        default:
            break;
        }
    }
}

