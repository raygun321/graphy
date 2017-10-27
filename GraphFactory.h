#include <Graph.h>
#include <string>

class GraphFactory
{

public:
	GraphFactory();
	GraphFactory(double step, double turn);
	virtual ~GraphFactory();

	/*
	 * Pass a pattern representing the graph to construct
	 */
	Graph generate(const std::string & pattern) const;

private:
	double _turnAngle;
	double _stepDistance;

};
