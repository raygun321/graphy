#pragma once

#include <vector>

abstract class OGLShape {
public:

  static void printVertexNames(const Graph&);
private:
	// Holds the buffer Ids for any arrays of vertex data
  std::vector<GLuint> _vbos;
  
  // Holds the Id for the vertex array object 
  GLuint _vao;
  
};