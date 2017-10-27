#pragma once

#include <boost/graph/adjacency_list.hpp>
#include <Vector2.h>
#include <SFML/Graphics.hpp>

// Vertex Properties
struct VertexProperty
{
  char label;
  Vector2d position;
};

// Edge Properties
struct EdgeProperty
{
  std::string label;
};


  /*
  * The generic class for a graph in Boost is adjacency_list.
  * Up to 7 template parameters can be given, for example:
  * typedef boost::adjacency_list<     boost::listS,       // out-edges stored in a std::list
  *                       boost::vecS,                     // vertex set stored here
  *                       boost::undirectedS,              // bidirectional graph.
  *                       boost::no_property,              // vertex properties
  *                       EdgeWeightProperty,              // edge properties
  *                       boost::no_property,              // graph properties
  *                       boost::listS                     // edge storage
  *                       > graph_t;
  *
  * The 'S' at the end of the choices (vecS, etc.) stands for 'S'elector.
  */
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, VertexProperty, EdgeProperty> Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
