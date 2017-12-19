#include <Graph.h>
#include <string>
#include <vector>

struct Rule {
    char node;
    std::string pattern;
    
    Rule() {}
    Rule(const char nodeChar, const std::string & patternStr) : node(nodeChar), pattern(patternStr) { }
};

class GraphNodeReplacer
{

public:
	GraphNodeReplacer();
	GraphNodeReplacer(const char node, const std::string & pattern);
	virtual ~GraphNodeReplacer();

  /*
   * Add a rule to the replacer
   */
  GraphNodeReplacer * addRule( const char node, const std::string & pattern );
  GraphNodeReplacer * addRule( const Rule & );

	/*
	 * Pass a pattern representing the graph to construct
	 */
	Graph replace(Graph &) const;

private:
  std::vector<Rule> _ruleVector;

};
