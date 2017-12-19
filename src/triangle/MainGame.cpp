#include "MainGame.h"
#include <OpenGL/gl3.h>

#include <iostream>

MainGame::MainGame() {
    _gameState = GameState::PLAY;
     
    _windowSizeX = 1024;
    _windowSizeY = 768;
    
    _rotate = true;
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
//    _window.create(sf::VideoMode(_windowSizeX, _windowSizeY), "Game Engine");
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
    
    if(!sf::Shader::isAvailable() )  {
        std::cout << "Shaders are not available" << std::endl;
        exit(-1);
    }
    
    if(!_shader.loadFromMemory(_vertexShader, sf::Shader::Vertex)) {
        std::cout << "Error loading vertex shader:" << std::endl;
        exit(-1);
    }

    if(!_shader.loadFromMemory(_fragmentShader,  sf::Shader::Fragment)) {
        std::cout << "Error loading fragment shader:" << std::endl;
        exit(-1);
    }

    // Prepare OpenGL
    float points[] = {
     0.0f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f 
    };

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);
    
    _vao = 0;
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
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
    if(!_font.loadFromFile("resources/Verdana.ttf")) {
        std::cout << "Error loading font" << std::endl;
        exit(-1);
		}
		
		// Text
		_text.setFont(_font);
		_text.setCharacterSize(24);
		_text.setFillColor(sf::Color::White);
}

void MainGame::gameLoop() {
    float angle=0;

    // Perform OpenGL initializations
		glMatrixMode(GL_PROJECTION);

    while(_gameState != GameState::EXIT) {
        processInput();
        
        // Activate the window
        _window.setActive(true);
                        
				_window.popGLStates();

        // Draw...
        // Eventually use a rendering thread - https://www.sfml-dev.org/tutorials/2.4/window-opengl.php
        // Apply some transformations for the cube
        sf::Shader::bind(&_shader);
        glBindVertexArray(_vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        sf::Shader::bind(NULL);

		    _window.pushGLStates();
        
        // End the current frame (internally swaps the front and back buffers)        
        _window.display();
        
        // Deactivate the window
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
            if(event.key.code == sf::Keyboard::A) {
                _rotate = !_rotate;
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

