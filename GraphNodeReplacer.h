#include <Graph.h>
#include <string>

class GraphNodeReplacer
{

public:
	GraphNodeReplacer(char node, std::string pattern);
	virtual ~GraphNodeReplacer();

	/*
	 * Pass a pattern representing the graph to construct
	 */
	Graph replace(Graph &) const;

private:
	char _searchNode;
	std::string _replacementPattern;

};
