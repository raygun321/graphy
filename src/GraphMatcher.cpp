#include <GraphMatcher.h>

void GraphMatcher::computeDistanceMatrix() {

	// Initialize
	// TODO: Is this really needed?
	if(_distanceMatrix.capacity() < _numVertex)
		_distanceMatrix.reserve(_numVertex);
	
	for(int i = 0; i < _numVertex; ++i) {
		if(_distanceMatrix[i].capacity() < _numVertex)
			_distanceMatrix[i].reserve(_numVertex);

		for(int j = 0; j < _numVertex; ++j) {
			_distanceMatrix[i][j] = 0;
		}
		
		breadth_first_search(_g, i, visitor(record_distance_number(&_distanceMatrix[i][0])));
	}
	
	
	
	

}

template <typename DistanceMap>
class distance_number_recorder : public default_bfs_visitor
{
  public:
    distance_number_recorder(DistanceMap dist) : d(dist) { }

    template <typename Edge, typename Graph>
    void tree_edge(Edge e, const Graph& g) const {
      typename graph_traits<Graph>::vertex_descriptor
			u = source(e, g), v = target(e, g);
			d[v] = d[u] + 1;
		}
  private:
      DistanceMap d;
  };

  // Convenience function
  template <typename DistanceMap>
  distance_number_recorder<DistanceMap>
  record_distance_number(DistanceMap d)
  {
    return distance_number_recorder<DistanceMap>(d);
  }
