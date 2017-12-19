#pragma once

#include <SFML/OpenGL.hpp>

#include <memory>
#include "State.h"

class VBO {
public:

  VBO();
  VBO(GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage);
  
  ~VBO();
  
  void generate();
  
  void bind(GLenum target);
  void bind();
  void unbind_all();
  
  void data(GLsizeiptr size, const GLvoid * data, GLenum usage);
  
  int getId();
  
  int getAttribute();
  void setAttribute(int number);
  void setState(State state) {_state = state;};
  void setIndexBuffer(bool flag) {_isIndexBuffer = flag;};
  bool isIndexBuffer() { return _isIndexBuffer;};
  GLint getCoordinateSize() {return _coordSize; };
  void setCoordinateSize(GLint coordSize) { _coordSize = coordSize; };
  GLenum getDataType() {return _dataType; };
  void setDataType(GLenum type) {_dataType = type; };
    
private:
  GLuint _id;
  GLenum _target;
  State _state;
  GLuint _attribute;
  bool _isIndexBuffer;
  GLint _coordSize;
  GLenum _dataType;
};

typedef std::shared_ptr<VBO> VBO_ptr;

/*
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);
    
    _vao = 0;
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
*/
