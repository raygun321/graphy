#include "RawModel.h"

RawModel::RawModel(VAO_ptr vao, int vertexCount) {
  _vao = vao;
  _vertexCount = vertexCount;
}
  
RawModel::~RawModel() {}
  
int RawModel::getVertexCount() {
  return _vertexCount;
}
    
VAO_ptr RawModel::getVAO() {
  return _vao;
}
