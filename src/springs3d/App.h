#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Renderer.h"
#include "Loader.h"
#include "Entity.h"
#include "StaticShader.h"
#include "Camera.h"
#include "RandomGraphFactory.h"

enum class AppState { RUN, EXIT };

class App {
public:
    App();
    ~App();
    void run();
  
private:
    void initSystems();
    void appLoop();
    void processInput();
    
    void initialize_vertex_position();
    void build_graph_display();
    void recalculate_vertex_position();

    glm::vec3 compute_neighbor_force(const glm::vec3 &currentPosition, const glm::vec3 &neighborPosition);
    glm::vec3 compute_foreign_force(const glm::vec3 &currentPosition, const glm::vec3 &neighborPosition);

    RandomGraphFactory _graphFactory;
    Graph _graph;
    
    Renderer_ptr _renderer;
    Loader _loader;
    StaticShader_ptr _shader;
    Camera_ptr _camera;
    
    TexturedModel_ptr _nodeModel;
    TexturedModel_ptr _linkModel;
    
    std::vector<Entity_ptr> _entities;
    
    AppState _appState;
    int _windowSizeX, _windowSizeY;
    sf::RenderWindow _window;
    sf::View _gameView;
    sf::View _statusBarView;
    sf::Font _font;
    sf::Text _text;
    
};
