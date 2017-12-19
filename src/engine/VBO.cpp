#include "VBO.h"

VBO::VBO() {
  _state = State::UNSET;
  _id = 0;
  _target = GL_ARRAY_BUFFER;  
  _attribute = 0;
  _isIndexBuffer = false;
}

VBO::VBO(GLenum target, GLsizeiptr size, const GLvoid * dataPtr, GLenum usage) {
  _target = target;
  
  generate();
  bind();
  data(size, dataPtr, usage);
}

VBO::~VBO() {
  if(_state != State::UNSET) {
    glDeleteBuffers(1, &_id);
    
    if(glGetError() != GL_NO_ERROR) {
      //TODO: Handle Error
    }
  }
}

void VBO::generate() {
  // Generate One Buffer
  glGenBuffers(1, &_id);
  
  if(glGetError() != GL_NO_ERROR) {
    //TODO: Handle Error
  }
  
  _state = State::CREATED;
}


void VBO::bind() {
  if(_state == State::CREATED || _state == State::BOUND) {
    glBindBuffer(_target, _id);

    if(glGetError() != GL_NO_ERROR) {
      //TODO: Handle Error
    }
      
    _state = State::BOUND;
  } else {
    //TODO: Handle Error
  }
} 

void VBO::bind(GLenum target) {
  _target = target;
  bind();
}
  
void VBO::unbind_all() {
  glBindBuffer(_target, 0);
  if(glGetError() != GL_NO_ERROR) {
    //TODO: Handle Error
  }
}
  
void VBO::data(GLsizeiptr size, const GLvoid * data, GLenum usage) {
  if(_state == State::BOUND) {
    glBufferData(_target, size, data, usage);

    if(glGetError() != GL_NO_ERROR) {
      //TODO: Handle Error
    }
      
    _state = State::BOUND;
  } else {
    //TODO: Handle Error
  }
}
  
int VBO::getId() {
  return _id;
}

int VBO::getAttribute() {
  return _attribute;
}

void VBO::setAttribute(int number) {
  _attribute = number;
}

    
