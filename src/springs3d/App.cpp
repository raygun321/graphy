#include "App.h"
#include <OpenGL/gl3.h>

#include <iostream>
#include "ModelTexture.h"
#include "OBJLoader.h"

#include "Utility.h"
#include "Util.h"

#include "config.h"

App::App() {
    _appState = AppState::RUN;
     
    _windowSizeX = 2048;
    _windowSizeY = 1536;
}

App::~App() {
    if(_window.isOpen())
        _window.close();
}

void App::run() {
    initSystems();
    
    appLoop();
}
  
void App::initSystems() {
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
    
    std::string sphereModelPath = graphy_RESOURCE_PATH;
    sphereModelPath += "/resources/icosphere_1.obj";
    std::string sphereTexturePath = graphy_RESOURCE_PATH;
    sphereTexturePath += "/resources/icosphere_128.png";
    
    std::string cubeModelPath = graphy_RESOURCE_PATH;
    cubeModelPath += "/resources/cube.obj";
    std::string cubeTexturePath = graphy_RESOURCE_PATH;
    cubeTexturePath += "/resources/cube.png";

    RawModel_ptr rModel = OBJLoader::loadObjModel(sphereModelPath, _loader);
    ModelTexture_ptr texture = _loader.loadTexture(sphereTexturePath);
    _nodeModel = std::make_shared<TexturedModel>(rModel, texture);
    
    rModel = OBJLoader::loadObjModel(cubeModelPath, _loader);
    texture = _loader.loadTexture(cubeTexturePath);
    _linkModel = std::make_shared<TexturedModel>(rModel, texture);
    
    _shader = std::make_shared<StaticShader>();
    _shader->init();
    
    _renderer = std::make_shared<Renderer>((float)_windowSizeY/(float)_windowSizeX, 
                                           _shader->getProjectionMatrixLocation(),
                                           _shader);
    
    _camera = std::make_shared<Camera>(glm::vec3(0,0,150), glm::vec3(0,0,0));
    
    // Graph
	_graphFactory.setDefaultNumVectors(50);
	_graphFactory.setDefaultEdgesPerVector(1.25);
	_graph = _graphFactory.generate();
	  
	initialize_vertex_position();
    
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

void App::appLoop() {

    // Perform OpenGL initializations
	glMatrixMode(GL_PROJECTION);
    
    int loopCount = -1;
    glm::vec3 origin(0,0,0);

    while(_appState != AppState::EXIT) {
        ++loopCount;

        processInput();
        
        // Game Logic
        
        float slowFactor = 500.0;
        glm::vec3 camPos = _camera->getRotation();
        camPos.x = sin(loopCount / slowFactor) * 150.0;
        camPos.y = 0;
        camPos.z = cos(loopCount / slowFactor) * 150.0;
        _camera->setPosition(camPos);
//        _camera->lookAt(origin);
        glm::vec3 camAng = _camera->getRotation();
        camAng.y = -(loopCount / slowFactor);
        _camera->setRotation(camAng);
        
        recalculate_vertex_position();
        _entities.clear();
        build_graph_display();

        // SFML... Activate the window
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        _window.clear(sf::Color::Black);
        _window.setView(_gameView);
        _window.setActive(true);
        _window.popGLStates();

        // Prep...
        _renderer->prepare();
        _shader->start();
        _shader->loadViewMatrix(_camera);

        // Draw...
        for(int i = 0; i < _entities.size(); ++i) {
          _renderer->render(_entities[i], _shader);
        }
        _shader->stop();

        // SFML... Draw and Deactivate
        _window.pushGLStates();
        
        _window.setView(_statusBarView);
        
        std::ostringstream oss;
        oss << " Camera - x: " << camPos.x << " y: " << camPos.y << " z: " << camPos.z;
        oss << " Angle - x: " << camAng.x << " y: " << camAng.y << " z: " << camAng.z;
        _text.setString(oss.str());
        _text.setPosition(20.0, 10.0);
//        std::cout << oss.str() << std::endl;
        
        _window.display();
        _window.setActive(false);
        _window.draw(_text);
    }
}

void App::processInput() {
    sf::Event event;
    while (_window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            _appState = AppState::EXIT;
        case sf::Event::KeyPressed:
            if(event.key.code == sf::Keyboard::W) {
              _camera->increasePosition(0, 0, -1.0f);
            } else if(event.key.code == sf::Keyboard::S) {
              _camera->increasePosition(0, 0, 1.0f);
            } else if(event.key.code == sf::Keyboard::D) {
              _camera->increasePosition(1.0f, 0, 0);
            } else if(event.key.code == sf::Keyboard::A) {
              _camera->increasePosition(-1.0f, 0, 0);
            } else if(event.key.code == sf::Keyboard::Space) {
    				// Regenerate Graph
						  _graph = _graphFactory.generate();
						  initialize_vertex_position();
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


void App::initialize_vertex_position() {
    int min = -50;
    int max = 50;
	typedef boost::graph_traits<Graph>::vertex_iterator iter_t;
  for (std::pair<iter_t, iter_t> p = vertices(_graph); p.first != p.second; ++p.first) {
	  _graph[*p.first].position = glm::vec3(	Utility::randomInt(min, max),	Utility::randomInt(min, max), Utility::randomInt(min, max) );
  }
}


void App::build_graph_display() {
	typedef boost::graph_traits<Graph>::vertex_iterator iter_t;
  for (std::pair<iter_t, iter_t> p = vertices(_graph); p.first != p.second; ++p.first) {
    Entity_ptr tempEntity = std::make_shared<Entity>(_nodeModel, 
                                                     _graph[*p.first].position, 
                                                     glm::vec3(0, 0, 0), 1.0f);
    _entities.push_back(tempEntity);
  }
  
  auto edgeIteratorRange = boost::edges(_graph);
  for(auto edgeIterator = edgeIteratorRange.first; edgeIterator != edgeIteratorRange.second; ++edgeIterator) {
    glm::vec3 sourcePosition = _graph[boost::source(*edgeIterator, _graph)].position;
	glm::vec3 targetPosition = _graph[boost::target(*edgeIterator, _graph)].position;
    glm::vec3 edgeVector = sourcePosition - targetPosition;
	glm::vec3 position = sourcePosition + targetPosition;
    position.x /= 2;
    position.y /= 2;
    position.z /= 2;

    float length = glm::length(edgeVector);
    
    glm::quat rotation = Util::rotationBetweenVectors(glm::vec3(0, 1, 0), edgeVector);
    
    Entity_ptr tempEntity = std::make_shared<Entity>(_linkModel, 
                                                     position, 
                                                     rotation, 
                                                     glm::vec3(0.1, length/2, 0.1));
    _entities.push_back(tempEntity);
  }
}



glm::vec3 App::compute_neighbor_force(const glm::vec3 &currentPosition, const glm::vec3 &neighborPosition) {
	const double c1 = 2.0;
	const double c2 = 10;
	const int c3 = 100;
	const double minForce = 0.1;

	double distance = glm::distance(currentPosition,neighborPosition);
	float forceScale =  c1 * log( distance / c2);
	if(forceScale < minForce) forceScale = 0;

	glm::vec3 displacement = neighborPosition;
	displacement -= currentPosition;	

	// generate a repulsive force if too close
	if(distance < (c2 / 2)) { 
		displacement = currentPosition;
		displacement -= neighborPosition;
		forceScale = c3 / pow(distance, 2);
	}

    displacement = glm::normalize(displacement);

    return displacement * forceScale;
}

glm::vec3 App::compute_foreign_force(const glm::vec3 &currentPosition, const glm::vec3 &neighborPosition) {
	const int c3 = 100;
	const double minForce = 0.1;
	
	glm::vec3 displacement = currentPosition;
	displacement -= neighborPosition;

  // c3 / d^2
	displacement = glm::normalize(displacement);
	double distance = glm::distance(currentPosition,neighborPosition);
	float forceScale =  c3 / pow(distance, 2);

	// Limit jitter
	if(forceScale < minForce) forceScale = 0;
		
	displacement = displacement * forceScale;

	return displacement;
}

void App::recalculate_vertex_position() {
	const float forceScaler = 0.1;
	typedef boost::graph_traits<Graph>::vertex_iterator iter_t;
	typedef boost::graph_traits < Graph >::adjacency_iterator adjacency_iterator;
	
	// Loop through all nodes to adjust position
  for (std::pair<iter_t, iter_t> p = vertices(_graph); p.first != p.second; ++p.first) {
  	glm::vec3 currentPosition = _graph[*p.first].position;
	  glm::vec3 currentForce(0,0,0);
	  
	  // Loop through all nodes to calculate forces
	  for (std::pair<iter_t, iter_t> neighbors = vertices(_graph); neighbors.first != neighbors.second; ++neighbors.first) {

	  	// Is this a different node?
	  	if(p.first != neighbors.first) {
	  		glm::vec3 neighborPosition = _graph[*neighbors.first].position;

				// Is this a neighbor?
				std::pair<Graph::edge_descriptor, bool> edgePair1 = boost::edge(*p.first, *neighbors.first, _graph);
				std::pair<Graph::edge_descriptor, bool> edgePair2 = boost::edge(*neighbors.first, *p.first, _graph);
				if(edgePair1.second || edgePair2.second ) {
					currentForce += compute_neighbor_force(currentPosition, neighborPosition);
				} else {
					currentForce += compute_foreign_force(currentPosition, neighborPosition);				
				}
	  	}
	  }
    
    currentPosition += currentForce * forceScaler;
/*
    if(currentPosition.x() < 0.0) currentPosition.setX(1.0);
    if(currentPosition.x() > 1000.0) currentPosition.setX(999.0);
    if(currentPosition.y() < 0.0) currentPosition.setY(1.0);
    if(currentPosition.y() > 1000.0) currentPosition.setY(999.0);
*/    
    _graph[*p.first].position = currentPosition;
  }
}


