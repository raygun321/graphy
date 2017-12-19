#include "SFGraphTransformer.h"
#include "Utility.h"
#include <iostream>

SFGraphTransformer::SFGraphTransformer() { }

SFGraphTransformer::SFGraphTransformer(unsigned int scale) :
		_renderScale(scale)
{
}

SFGraphTransformer::~SFGraphTransformer() { }



SHAPES SFGraphTransformer::build(const Graph &g) {
  SHAPES shapes;

  boost::graph_traits<Graph>::vertex_iterator i, end;
  for (boost::tie(i, end) = vertices(g); i != end; ++i) {
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

  auto edgeIteratorRange = boost::edges(g);
  for(auto edgeIterator = edgeIteratorRange.first; edgeIterator != edgeIteratorRange.second; ++edgeIterator)
	{
	    // Get angle
		Vector2d sourcePosition = g[boost::source(*edgeIterator, g)].position; // Source Position

		Vector2d edgeVector = sourcePosition;
		edgeVector.setY(0 - edgeVector.y()); // Invert Y for angle

		Vector2d targetPosition = g[boost::target(*edgeIterator, g)].position;
		targetPosition.setY(0 - targetPosition.y()); // Invert Y for angle

		edgeVector -= targetPosition; // Minus Target Position

//		std::cout << "Source: " << sourcePosition << std::endl;
//		std::cout << "Dest: " << targetPosition << std::endl;

		double length = edgeVector.length();


		double angle = edgeVector.angle();

//		std::cout << "Angle: " << angle << std::endl;

		sf::RectangleShape * edgeRectangle = new sf::RectangleShape();
		edgeRectangle->setSize(sf::Vector2f(length * _renderScale, 3));
		edgeRectangle->setPosition(sourcePosition.x() *_renderScale, sourcePosition.y()*_renderScale + 1);
		if(angle == 90)
			edgeRectangle->rotate(180);
		if(angle > 0)
            edgeRectangle->rotate(360 - angle); // SFML degrees are clockwise
		else if(angle > -90)
			edgeRectangle->rotate(0 - angle);
		else
			edgeRectangle->rotate(-90);

//		std::cout << "Rect: " << Vector2d(sourcePosition.x() *_renderScale, sourcePosition.y()*_renderScale) <<  std::endl;
//		std::cout << "Angle: " << angle << ":" << 360 - angle <<  std::endl;
//		std::cout << std::endl;

		edgeRectangle->setFillColor(sf::Color::White);
		shapes.push_back(edgeRectangle);
	}
  return shapes;
}
