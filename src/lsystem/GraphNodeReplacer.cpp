#include "GraphNodeReplacer.h"

GraphNodeReplacer::GraphNodeReplacer(const char node, const std::string & pattern) {
  Rule initialRule(node, pattern);
  _ruleVector.push_back(initialRule);
}

GraphNodeReplacer::~GraphNodeReplacer() { }

GraphNodeReplacer * GraphNodeReplacer::addRule( const char node, const std::string & pattern ) {
  Rule newRule(node, pattern);
  return addRule(newRule);
}

GraphNodeReplacer * GraphNodeReplacer::addRule( const Rule & rule ) {
  _ruleVector.push_back(rule);
  return this;
}

Graph GraphNodeReplacer::replace(Graph &g) const {
    boost::graph_traits<Graph>::vertex_iterator node, end;
    
    for (boost::tie(node, end) = vertices(g); node != end; ++node) {
      for (auto rule : _ruleVector) {
        if(g[*node].label == rule.node) {
          std::cout << "Hurray!" << std::endl;
          // Now how do we tell what leads and follows?
          // Use the left side of edges for leading edges
          // Use the right side of edges for trailing edges
        }
      }
    }
/*
    
    	// Do we need to replace this node
    	if(g[*i].label == _searchNode) {

    	}
        double radius = 4.0;
        sf::CircleShape * circle = new sf::CircleShape();
        sf::RectangleShape * forceRectangle = new sf::RectangleShape();
        Vector2d positionVec =  g[*i].position;
        circle->setRadius(radius);
        circle->setPosition(positionVec.x() *_renderScale - radius, positionVec.y()*_renderScale - radius);
        circle->setFillColor(sf::Color::Transparent);
        sf::Color color;

	    auto mapColor = _colorMap.find( g[*i].label );
	    if(mapColor == _colorMap.end()) {
	      color = sf::Color(Utility::randomInt(0, 255),Utility::randomInt(0, 255),Utility::randomInt(0, 255) );
	      _colorMap[ g[*i].label ] = color;
	    } else {
	      color = mapColor->second;
	    }

	    circle->setOutlineColor(color);
	    circle->setOutlineThickness(2);
	    shapes.push_back(circle);
	  }
*/
	return g;
}

