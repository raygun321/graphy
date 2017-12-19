#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <random>
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */
#include "Vector2.h"
#include "Utility.h"
#include "RandomGraphFactory.h"
#include <boost/graph/adjacency_list.hpp> 

#define RENDER_SCALE 10

void initialize_vertex_position(Graph &g) {
	typedef boost::graph_traits<Graph>::vertex_iterator iter_t;
  for (std::pair<iter_t, iter_t> p = vertices(g); p.first != p.second; ++p.first) {
	  g[*p.first].position.set(	Utility::randomInt(100 / RENDER_SCALE, 900 / RENDER_SCALE ),	Utility::randomInt(100 / RENDER_SCALE, 900 / RENDER_SCALE) );
	  sf::Color color(Utility::randomInt(0, 255),Utility::randomInt(0, 255),Utility::randomInt(0, 255) );
	  g[*p.first].color = color;
  }
}

Vector2d compute_neighbor_force(const Vector2d &currentPosition, const Vector2d &neighborPosition) {
	const double c1 = 2.0;
	const double c2 = 10;
	const int c3 = 100;
	const double minForce = 0.1;

	double distance = currentPosition.distance(neighborPosition);
	double forceScale =  c1 * log( distance / c2);
	if(forceScale < minForce) forceScale = 0;

	Vector2d displacement = neighborPosition;
	displacement -= currentPosition;	

	// generate a repulsive force if too close
	if(distance < (c2 / 2)) { 
		displacement = currentPosition;
		displacement -= neighborPosition;
		forceScale = c3 / pow(distance, 2);
	}

	displacement = displacement.normalize();

	return displacement.scale(forceScale);
}

Vector2d compute_foreign_force(const Vector2d &currentPosition, const Vector2d &neighborPosition) {
	const int c3 = 100;
	const double minForce = 0.1;
	
	Vector2d displacement = currentPosition;
	displacement -= neighborPosition;

  // c3 / d^2
	displacement = displacement.normalize();
	double distance = currentPosition.distance(neighborPosition);
	double forceScale =  c3 / pow(distance, 2);

	// Limit jitter
	if(forceScale < minForce) forceScale = 0;
		
	displacement = displacement.scale(forceScale);

	return displacement;
}

void recalculate_vertex_position(Graph &g) {
	const double forceScaler = 0.1;
	typedef boost::graph_traits<Graph>::vertex_iterator iter_t;
	typedef boost::graph_traits < Graph >::adjacency_iterator adjacency_iterator;
	
	// Loop through all nodes to adjust position
  for (std::pair<iter_t, iter_t> p = vertices(g); p.first != p.second; ++p.first) {
  	Vector2d currentPosition = g[*p.first].position;
	  Vector2d currentForce(0,0);

	  
	  // Loop through all nodes to calculate forces
	  for (std::pair<iter_t, iter_t> neighbors = vertices(g); neighbors.first != neighbors.second; ++neighbors.first) {

	  	// Is this a different node?
	  	if(p.first != neighbors.first) {
	  		Vector2d neighborPosition = g[*neighbors.first].position;

				// Is this a neighbor?
				std::pair<Graph::edge_descriptor, bool> edgePair1 = boost::edge(*p.first, *neighbors.first, g);
				std::pair<Graph::edge_descriptor, bool> edgePair2 = boost::edge(*neighbors.first, *p.first, g);
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
    g[*p.first].position = currentPosition;     
  }
}


typedef std::vector< sf::Shape * > SHAPES;

SHAPES build_graph_display(const Graph &g) {
  SHAPES shapes;
  
	typedef boost::graph_traits<Graph>::vertex_iterator iter_t;
  for (std::pair<iter_t, iter_t> p = vertices(g); p.first != p.second; ++p.first) {
  	double radius = 4.0;
		sf::CircleShape * circle = new sf::CircleShape();
		sf::RectangleShape * forceRectangle = new sf::RectangleShape();
		Vector2d positionVec =  g[*p.first].position;
		circle->setRadius(radius);
		circle->setPosition(positionVec.x() *RENDER_SCALE - radius, positionVec.y()*RENDER_SCALE - radius);
		circle->setFillColor(sf::Color::Transparent);
		circle->setOutlineColor(g[*p.first].color);
		circle->setOutlineThickness(2);
    shapes.push_back(circle);
  }
  
  auto edgeIteratorRange = boost::edges(g);
  for(auto edgeIterator = edgeIteratorRange.first; edgeIterator != edgeIteratorRange.second; ++edgeIterator)
	{
		Vector2d sourcePosition = g[boost::source(*edgeIterator, g)].position; // Source Position
		Vector2d edgeVector = sourcePosition;
		edgeVector -= g[boost::target(*edgeIterator, g)].position; // Minus Target Position
		
		double length = edgeVector.length();
		double angle = edgeVector.angle();

		sf::RectangleShape * edgeRectangle = new sf::RectangleShape();
		edgeRectangle->setSize(sf::Vector2f(length * RENDER_SCALE, 1));
		edgeRectangle->setPosition(sourcePosition.x() *RENDER_SCALE, sourcePosition.y()*RENDER_SCALE);
		edgeRectangle->rotate(angle);
		edgeRectangle->setFillColor(sf::Color::White);
		shapes.push_back(edgeRectangle);
  }
  return shapes;
}


void initializeViews(sf::RenderWindow &window, sf::View &graphView, sf::View &statusView) {
	graphView.setSize(sf::Vector2f(1000, 950));
	graphView.setCenter(sf::Vector2f(500, 475));
	graphView.setViewport(sf::FloatRect(0, 0, 1, 0.95f));
	
	statusView.setSize(sf::Vector2f(1000, 50));
	statusView.setCenter(sf::Vector2f(500, 25));
	statusView.setViewport(sf::FloatRect(0, 0.95f, 1, 0.05f));
}

void initializeFontAndText(sf::Font &font, sf::Text&text) {
	if(!font.loadFromFile("resources/Verdana.ttf")) {
		std::cout << "Error loading font" << std::endl;
		exit(-1);
	}
	
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
}


int main() {
	int iterations = 0;
  int step = 50;
  srand(time(NULL));
  sf::View graphView;
  sf::View statusView;
  sf::RenderWindow window(sf::VideoMode(1000, 1000), "Dungraph Test");
  
  initializeViews(window, graphView, statusView);

  sf::Font font;
	sf::Text text;
	initializeFontAndText(font, text);

	RandomGraphFactory graphFactory;
	graphFactory.setDefaultNumVectors(100);
	graphFactory.setDefaultEdgesPerVector(1.25);
	Graph g = graphFactory.generate();
	initialize_vertex_position(g);

  SHAPES shapes = build_graph_display(g);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
    	switch (event.type) {

    		case sf::Event::Closed:
    			window.close();
    			break;
    			
    		case sf::Event::KeyPressed:
    			if(event.key.code == sf::Keyboard::Space) {
    				// Regenerate Graph
						g = graphFactory.generate();
						initialize_vertex_position(g);
    				iterations = 0;	
    			} else if (event.key.code == sf::Keyboard::Add || event.key.code == sf::Keyboard::Equal) {
//    				sf::View view = window.getView();
//						view.zoom(0.5f);
//						window.setView(view);
						graphView.zoom(0.5f);
                                                step = step / 2;
    			} else if (event.key.code == sf::Keyboard::Subtract || event.key.code == sf::Keyboard::Dash) {
						graphView.zoom(2.0f);
                                                step = step * 2;
    			} else if (event.key.code == sf::Keyboard::Up) {
						graphView.move(0, 0 - step);
    			} else if (event.key.code == sf::Keyboard::Down) {
						graphView.move(0, step);
    			} else if (event.key.code == sf::Keyboard::Left) {
						graphView.move(0 - step, 0);
    			} else if (event.key.code == sf::Keyboard::Right) {
						graphView.move(step, 0);
    			} else if (event.key.code == sf::Keyboard::Numpad2) {
						graphFactory.setDefaultNumVectors(graphFactory.defaultNumVectors() - 5);
						g = graphFactory.generate();
						initialize_vertex_position(g);
    				iterations = 0;	
    			} else if (event.key.code == sf::Keyboard::Numpad8) {
    				graphFactory.setDefaultNumVectors(graphFactory.defaultNumVectors() + 5);
						g = graphFactory.generate();
						initialize_vertex_position(g);
    				iterations = 0;	
    			} else if (event.key.code == sf::Keyboard::Numpad4) {
    				graphFactory.setDefaultEdgesPerVector(graphFactory.defaultEdgesPerVector() - 0.25);
						g = graphFactory.generate();
						initialize_vertex_position(g);
    				iterations = 0;	
    			} else if (event.key.code == sf::Keyboard::Numpad6) {
    				graphFactory.setDefaultEdgesPerVector(graphFactory.defaultEdgesPerVector() + 0.25);
						g = graphFactory.generate();
						initialize_vertex_position(g);
    				iterations = 0;	
    			}
    			break;

    		default:
    			break;
    	}
    }
    if(iterations < 10000) {
    	for ( int i = 0; i < shapes.size(); ++i) {
    		delete shapes[i];
    	}
	   	recalculate_vertex_position(g);
 	  	iterations++;
	   	shapes = build_graph_display(g);
	   	std::ostringstream oss;
	   	oss << "Number of Vectors: " << graphFactory.defaultNumVectors() 
	   			<< ", Edges Per Vector: " << graphFactory.defaultEdgesPerVector() << ", Iterations: " << iterations  ;
	   	text.setString(oss.str());
	   	text.setPosition(20, 10);
	  }
    window.clear();
    window.setView(graphView);
    for (int i = 0; i < shapes.size(); ++i) {
      window.draw(*shapes[i]);
    }
    window.setView(statusView);
    window.draw(text);
    window.setView(graphView);

    window.display();
//    usleep(100000);
  }

  return 0;
}

