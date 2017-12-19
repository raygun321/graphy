#include <RandomGraphFactory.h>
#include <Utility.h>

RandomGraphFactory::RandomGraphFactory() :
_numVectors(25),
_numEdgesPerVectors(1.5) {
}


Graph RandomGraphFactory::generate() const {
	return generate(_numVectors, _numEdgesPerVectors);
}

Graph RandomGraphFactory::generate(const int numVectors, const float edgesPerVector) const {
	Graph g;

	// Add vertices
	for(int i = 0; i < numVectors; ++i) {
		boost::add_vertex(g);
	}
	
	// Generate N edges for each Vector
	// We are not avoiding self loops or multiple edges between nodes
	for(int i=0; i < numVectors; ++i ) {
		int j;
		for(j=1; j <= edgesPerVector; ++j) {
			int edge = Utility::randomInt(0, numVectors - 1);
			// if(edge == i) edge = (i + 1) % (numVectors - 1);
			boost::add_edge(i, edge, g);
		}
		int chance = (edgesPerVector - j + 1) * 100;
		if( Utility::randomInt(1, 100) <= chance) {
			boost::add_edge(i, Utility::randomInt(0, numVectors - 1), g);
		}
	}
	
	return g;	
}


void RandomGraphFactory::setDefaultNumVectors(const int numVectors)
{
   _numVectors = numVectors;
}

int RandomGraphFactory::defaultNumVectors() const
{
   return _numVectors;
}


void RandomGraphFactory::setDefaultEdgesPerVector(const float edgesPerVector)
{
   _numEdgesPerVectors = edgesPerVector;
}

float RandomGraphFactory::defaultEdgesPerVector() const
{
   return _numEdgesPerVectors;
}

RandomGraphFactory::~RandomGraphFactory() { }
