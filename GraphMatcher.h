#include <Graph.h>
#include <vector>

typedef std::vector<std::vector<int> > DistanceMatrix;
class GraphMatcher
{

public:
	GraphMatcher();
	virtual ~GraphMatcher();

	Graph generate() const;
	Graph generate(const int numVectors, const float edgesPerVector) const;

	int defaultNumVectors() const;
	void setDefaultNumVectors(const int numVectors);
	
	float defaultEdgesPerVector() const;
	void setDefaultEdgesPerVector(const float edgesPerVector);

protected:
  Graph _g;

private:
  void computeDistanceMatrix();

  DistanceMatrix _distanceMatrix;
  int   _numVertex;
};
