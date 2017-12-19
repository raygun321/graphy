#include <Graph.h>

class RandomGraphFactory
{

public:
	RandomGraphFactory();
	virtual ~RandomGraphFactory();

	Graph generate() const;
	Graph generate(const int numVectors, const float edgesPerVector) const;

	int defaultNumVectors() const;
	void setDefaultNumVectors(const int numVectors);
	
	float defaultEdgesPerVector() const;
	void setDefaultEdgesPerVector(const float edgesPerVector);

protected:
	int _numVectors;
	float _numEdgesPerVectors;
};
