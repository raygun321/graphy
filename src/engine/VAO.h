#pragma once

#include <SFML/OpenGL.hpp>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <memory>
#include <vector>

#include "VBO.h"
#include "State.h"

class VAO {
public:

  VAO();  
  ~VAO();
  
  void generate();
  
  void bind();
  
  void unbind_all();

  void addIndexAttribute(int dataCount, GLuint data[]);
  void addIndexAttribute(std::vector<GLuint> &data);
  void addArrayAttribute(int attributeNumber,  int coordSize, int dataCount, GLfloat data[]);
  void addArrayAttribute(int attributeNumber,  int coordSize, std::vector<glm::vec2> &data);
  void addArrayAttribute(int attributeNumber,  int coordSize, std::vector<glm::vec3> &data);
  
  void enable();
  
  void disable_all();
  
  int getId();
private:
  void addAttribute(int attributeNumber, GLenum target, GLint coordinateSize, GLsizeiptr size, const GLvoid * data, bool indexFlag);

  GLuint _id;
  State _state;
  std::vector<VBO_ptr> _vbos;
};

typedef std::shared_ptr<VAO> VAO_ptr;
