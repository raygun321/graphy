#include "VAO.h"
#include <algorithm>
#include <OpenGL/gl3.h>

VAO::VAO() {
  _state = State::UNSET;
  _id = 0;
}

VAO::~VAO() {
  if(_state != State::UNSET) {
    glDeleteVertexArrays(1, &_id);
    
    if(glGetError() != GL_NO_ERROR) {
      //TODO: Handle Error
    }
  }
}

void VAO::generate() {
  // Generate One Buffer
  glGenVertexArrays(1, &_id);
  
  if(glGetError() != GL_NO_ERROR) {
    //TODO: Handle Error
  }
  
  _state = State::CREATED;
}


void VAO::bind() {
  if(_state == State::CREATED || _state == State::BOUND) {
    glBindVertexArray(_id);

    if(glGetError() != GL_NO_ERROR) {
      //TODO: Handle Error
    }
      
    _state = State::BOUND;
  } else {
    //TODO: Handle Error
  }
} 

  
void VAO::unbind_all() {
  glBindVertexArray(0);
  if(glGetError() != GL_NO_ERROR) {
    //TODO: Handle Error
  }
}


void VAO::disable_all() {
  std::for_each(_vbos.begin(), _vbos.end(), [](VBO_ptr vbo) {
    if(!vbo->isIndexBuffer()) {
      glDisableVertexAttribArray(vbo->getAttribute());
      if(glGetError() != GL_NO_ERROR) {
        //TODO: Handle Error
      }
    }
  } );
  
  if(_vbos.begin() != _vbos.end()) {
    (*_vbos.begin())->unbind_all();
  }
}


void VAO::addArrayAttribute(int attributeNumber,  int coordSize, int dataCount, GLfloat data[]) {
  addAttribute(attributeNumber, GL_ARRAY_BUFFER, coordSize, dataCount * sizeof(float), data, false);
}

void VAO::addArrayAttribute(int attributeNumber,  int coordSize, std::vector<glm::vec3> &data) {
  addAttribute(attributeNumber, GL_ARRAY_BUFFER, coordSize, data.size() * sizeof(glm::vec3), &data[0], false);
}

void VAO::addArrayAttribute(int attributeNumber,  int coordSize, std::vector<glm::vec2> &data) {
  addAttribute(attributeNumber, GL_ARRAY_BUFFER, coordSize, data.size() * sizeof(glm::vec2), &data[0], false);
}

void VAO::addIndexAttribute(int dataCount, GLuint data[]) {
  addAttribute(0, GL_ELEMENT_ARRAY_BUFFER, 0, dataCount * sizeof(int), data, true);
}

void VAO::addIndexAttribute(std::vector<GLuint> &data) {
  addAttribute(0, GL_ELEMENT_ARRAY_BUFFER, 0, data.size() * sizeof(GLuint), &data[0], true);
}

void VAO::addAttribute(int attributeNumber, GLenum target, GLint coordinateSize, GLsizeiptr size, const GLvoid * data, bool indexFlag) {
  if(_state == State::BOUND ) {
    VBO_ptr vbo = std::make_shared<VBO>();
    vbo->generate();
    vbo->bind(target);
    
    vbo->data(size, data, GL_STATIC_DRAW);
    vbo->setAttribute(attributeNumber);
    
    if(!indexFlag) {
      vbo->setCoordinateSize(coordinateSize);
      vbo->setDataType(GL_FLOAT);
      if(glGetError() != GL_NO_ERROR) {
        //TODO: Handle Error
      }

      glEnableVertexAttribArray(attributeNumber);
      vbo->bind(target);
      glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, false, 0, 0);
      if(glGetError() != GL_NO_ERROR) {
        //TODO: Handle Error
      }
    } else {
      vbo->setIndexBuffer(true);
    }

    _vbos.push_back(vbo);
  } else {
    //TODO: Handle Error
  }
}

void VAO::enable() {
  bind();
  
  std::for_each(_vbos.begin(), _vbos.end(), [](VBO_ptr vbo) {
    if(!vbo->isIndexBuffer()) {
      glEnableVertexAttribArray(vbo->getAttribute());
      if(glGetError() != GL_NO_ERROR) {
        //TODO: Handle Error
      }
      vbo->bind();
      glVertexAttribPointer(vbo->getAttribute(),
                            vbo->getCoordinateSize(),
                            vbo->getDataType(), false, 0, 0);
      if(glGetError() != GL_NO_ERROR) {
        //TODO: Handle Error
      }
    } else {
      vbo->bind();
    }
  } );
}
  
int VAO::getId() {
  return _id;
}
