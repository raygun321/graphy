#pragma once

#include <SFML/OpenGL.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <memory>
#include <string>

class ShaderProgram {
public:
  ShaderProgram(std::string vertexFile, std::string fragmentFile);
  ~ShaderProgram();
  
  void init();
  
  void start();
  
  void stop();
  
  void bindAttribute(int attribute, std::string variableName);

  virtual void bindAttributes() = 0;
  
  GLuint getUniformLocation(std::string uniformName);
  
  virtual void getAllUniformLocations() = 0;
  
  void loadUniform(GLuint location, float value);
  void loadUniform(GLuint location, bool value);
  void loadUniform(GLuint location, glm::vec3 value);
  void loadUniform(GLuint location, glm::mat4 value);
  
private:
  int loadShader(std::string file, GLuint type);

  GLuint _programId;
  GLuint _vertexShaderId;
  GLuint _fragmentShaderId;
};

typedef std::shared_ptr<ShaderProgram> ShaderProgram_ptr;

