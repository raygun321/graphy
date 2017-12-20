#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <random>
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */
#include "Vector2.h"
#include "Utility.h"
#include "GraphFactory.h"
#include "SFGraphTransformer.h"
#include <boost/utility.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/algorithm/string/replace.hpp>
#include "config.h"


std::ostream & operator<<(std::ostream & out, const Vector2d & v) {
        out << "( " << v.x() << ", " << v.y() << " )";
        return out;
}

void initializeViews(sf::RenderWindow &window, sf::View &graphView, sf::View &statusView) {
	graphView.setSize(sf::Vector2f(1000, 950));
	graphView.setCenter(sf::Vector2f(0, 0));
	graphView.setViewport(sf::FloatRect(0, 0, 1, 0.95f));
	
	statusView.setSize(sf::Vector2f(1000, 50));
	statusView.setCenter(sf::Vector2f(500, 25));
	statusView.setViewport(sf::FloatRect(0, 0.95f, 1, 0.05f));
}

void initializeFontAndText(sf::Font &font, sf::Text&text) {
    std::string fontPath = graphy_RESOURCE_PATH;
    fontPath += "/resources/Verdana.ttf";

	if(!font.loadFromFile(fontPath)) {
		std::cout << "Error loading font" << std::endl;
		exit(-1);
	}
	
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
}


std::string evolveString(const std::string & seed, 
                         const char find1,
                         const std::string & replace1,
                         const char find2,
                         const std::string & replace2) {
    std::string result;
    
    for(const char& c : seed) {
        if(c == find1) {
            result += replace1;
        } else if (c == find2) {
            result += replace2;
        } else {
            result += c;
        }
    }
    
    return result;
}
                         

int main() {
  int iterations = 0;
  int step = 50;
  srand(time(NULL));
  sf::View graphView;
  sf::View statusView;
  sf::RenderWindow window(sf::VideoMode(1000, 1000), "Dungraph Test");
  
  //  std::string graphSeed = "G<FJ>FK<FG>FJ";
  // F - Step Forward
  // < - Turn Left
  // > - Turn Right
  // [ - Push State on Stack
  // ] - Pop State from Stack
  // * - Any other is a node

/*// Sierpinski triangle --
  std::string graphSeed      = "A";
  char findChar1             = 'A';
  std::string replaceString1 = "BF<AF<BF";
  char findChar2             = 'B';
  std::string replaceString2 = "AF>BF>AF";
  double angle = 60.0;
*/

/*// Dragon Curve --
  std::string graphSeed      = "ZFX";
  char findChar1             = 'X';
  std::string replaceString1 = "X>YF>";
  char findChar2             = 'Y';
  std::string replaceString2 = "<FX<Y";
  double angle = 90.0
*/

// Plant --
  std::string graphSeed      = "XF";
  char findChar1             = 'X';
  std::string replaceString1 = "F[<X][X]F[<X]>FX";
  char findChar2             = 'F';
  std::string replaceString2 = "FF";
  double angle = 25.0;

  initializeViews(window, graphView, statusView);

  sf::Font font;
  sf::Text text;
  initializeFontAndText(font, text);

  GraphFactory graphFactory(1.0, angle);
  Graph g = graphFactory.generate(graphSeed);

  SFGraphTransformer transformer(50);
  SHAPES shapes = transformer.build(g);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
    	switch (event.type) {

    		case sf::Event::Closed:
    			window.close();
    			break;
    			
    		case sf::Event::KeyPressed:
    			if(event.key.code == sf::Keyboard::Space) {
    			  graphSeed = evolveString(graphSeed, findChar1, replaceString1,
    			                                      findChar2, replaceString2);
            g = graphFactory.generate(graphSeed);
			    	for ( int i = 0; i < shapes.size(); ++i) {
			    		delete shapes[i];
			    	}
				   	shapes = transformer.build(g);

    				iterations = 0;	
    			} else if (event.key.code == sf::Keyboard::Add || event.key.code == sf::Keyboard::Equal) {
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
    			}
    			break;

    		default:
    			break;
    	}
    }
     if(iterations < 10000) {
    	std::ostringstream oss;
	   	oss << "Graph Seed: " << graphSeed;
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
  }

  return 0;
}

