#include <GraphUtility.h>

void GraphUtility::printVertexNames(const Graph& g) {
  std::cout << "vertices(g) = { ";
  typedef boost::graph_traits<Graph>::vertex_iterator iter_t;
  for (std::pair<iter_t, iter_t> p = vertices(g); p.first != p.second; ++p.first) {
    std::cout  << g[*p.first].label << ' ';
  }
  std::cout << "}" << std::endl;
}
