#pragma once

#include <memory>
#include "VAO.h"

class RawModel {
public:

  RawModel(VAO_ptr vao, int vertexCount);
  
  ~RawModel();
  
  int getVertexCount();
    
  VAO_ptr getVAO();
private:
  VAO_ptr _vao;
  int _vertexCount;
};

typedef std::shared_ptr<RawModel> RawModel_ptr;

