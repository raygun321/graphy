#include <GraphNodeReplacer.h>

GraphNodeReplacer::GraphNodeReplacer(char node, std::string pattern) :
    _searchNode(node),
   _replacementPattern(pattern)
{
}

GraphNodeReplacer::~GraphNodeReplacer() { }

Graph GraphFactory::replace(Graph &g) const {
    boost::graph_traits<Graph>::vertex_iterator i, end;
    for (boost::tie(i, end) = vertices(g); i != end; ++i) {
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

	return g;
}

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
		Vector2d sourcePosition = g[boost::source(*edgeIterator, g)].position; // Source Position
		Vector2d edgeVector = sourcePosition;
		edgeVector -= g[boost::target(*edgeIterator, g)].position; // Minus Target Position

		double length = edgeVector.length();
		double angle = edgeVector.angle();

		sf::RectangleShape * edgeRectangle = new sf::RectangleShape();
		edgeRectangle->setSize(sf::Vector2f(length * _renderScale, 1));
		edgeRectangle->setPosition(sourcePosition.x() *_renderScale, sourcePosition.y()*_renderScale);
		edgeRectangle->rotate(360 - angle); // SFML degrees are clockwise

		edgeRectangle->setFillColor(sf::Color::White);
		shapes.push_back(edgeRectangle);
	}
  return shapes;
}
