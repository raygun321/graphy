#include <SFML/Graphics.hpp>
#include <Graph.h>
#include <string>
#include <map>

typedef std::vector< sf::Shape * > SHAPES;

class SFGraphTransformer
{

public:
	SFGraphTransformer();
	SFGraphTransformer(unsigned int scale);

	virtual ~SFGraphTransformer();

	/*
	 * Pass a graph to build a vector of shapes for rendering
	 */
	SHAPES build(const Graph &g);

	unsigned int getRenderScale() { return _renderScale; }
	void setRenderScale(unsigned int scale) { _renderScale = scale; }

private:
	unsigned int _renderScale;
	std::map<char, sf::Color> _colorMap;

};
