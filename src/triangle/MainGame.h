#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

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
    
    GameState _gameState;
    int _windowSizeX, _windowSizeY;
    sf::RenderWindow _window;
    sf::View _gameView;
    sf::View _statusBarView;
    sf::Font _font;
    sf::Text _text;
    
    bool _rotate;
    sf::Clock _clock;
    
/* OpenGL Version	GLSL Version	#version tag
1.2	none	none
2.0	1.10.59	110
2.1	1.20.8	120
3.0	1.30.10	130
3.1	1.40.08	140
3.2	1.50.11	150
3.3	3.30.6	330
4.0	4.00.9	400
4.1	4.10.6	410
4.2	4.20.6	420
4.3	4.30.6	430
*/
    // Shader
    sf::Shader _shader;
    
    // Vertex Shader positions the vertex
    const char* _vertexShader = //"vertex_shader.glsl";
"#version 400\n"
"in vec3 vp;"
"void main() {"
"  gl_Position = vec4(vp, 1.0);"
"}";

    // Fragment Shaders color each fragment
    const char* _fragmentShader = //"fragment_shader.glsl";
"#version 400\n"
"out vec4 frag_colour;"
"void main() {"
"  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
"}";

    GLuint _vao;

};
