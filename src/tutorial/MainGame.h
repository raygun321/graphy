#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Renderer.h"
#include "Loader.h"
#include "Entity.h"
#include "StaticShader.h"
#include "Camera.h"
#include "Light.h"

enum class GameState { PLAY, EXIT };

class MainGame {
public:
    MainGame();
    ~MainGame();
    void run();
  
private:
    void initSystems();
    void gameLoop();
    void processInput();
    
    Renderer_ptr _renderer;
    Loader _loader;
    Entity_ptr _entity;
    StaticShader_ptr _shader;
    Camera_ptr _camera;
    Light_ptr _light;
    
    GameState _gameState;
    int _windowSizeX, _windowSizeY;
    sf::RenderWindow _window;
    sf::View _gameView;
    sf::View _statusBarView;
    sf::Font _font;
    sf::Text _text;
    
};
