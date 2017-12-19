#include "ShaderProgram.h"
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>


ShaderProgram::ShaderProgram(std::string vertexFile, std::string fragmentFile) {
  _vertexShaderId = loadShader(vertexFile, GL_VERTEX_SHADER);
  _fragmentShaderId = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
  _programId = glCreateProgram();
}

void ShaderProgram::init() {
  glAttachShader(_programId, _vertexShaderId);
  glAttachShader(_programId, _fragmentShaderId);
  bindAttributes();
  glLinkProgram(_programId);
  glValidateProgram(_programId);
  getAllUniformLocations();
}

ShaderProgram::~ShaderProgram() {
  stop();
  glDetachShader(_programId, _vertexShaderId);
  glDetachShader(_programId, _fragmentShaderId);
  glDeleteShader(_vertexShaderId);
  glDeleteShader(_fragmentShaderId);
  glDeleteProgram(_programId);
}
  
void ShaderProgram::start() {
  glUseProgram(_programId);
}
  
void ShaderProgram::stop() {
  glUseProgram(0);
}
  
void ShaderProgram::bindAttribute(int attribute, std::string variableName) {
  glBindAttribLocation(_programId, attribute, variableName.c_str());
}


GLuint ShaderProgram::getUniformLocation(std::string uniformName) {
  return glGetUniformLocation(_programId, uniformName.c_str());
}


void ShaderProgram::loadUniform(GLuint location, float value) {
  glUniform1f(location, value);
}

void ShaderProgram::loadUniform(GLuint location, bool value) {
  float newValue = value ? 1.0f : 0.0f;
  loadUniform(location, newValue);
}

void ShaderProgram::loadUniform(GLuint location, glm::vec3 value) {
  glUniform3fv(location, 1, &value[0]);
}

void ShaderProgram::loadUniform(GLuint location, glm::mat4 value) {
  glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}

int ShaderProgram::loadShader(std::string file, GLuint type) {
  // Read contents of file
  std::ifstream fileStream;
  std::string shaderSource = "";
    
  fileStream.open(file);
  if(!fileStream.is_open()) {
    std::cout << "Could not open file." << std::endl;
    exit(-1);
  }
    
  shaderSource.append((std::istreambuf_iterator<char>(fileStream)),
                       std::istreambuf_iterator<char>());
  
  GLuint shaderId = glCreateShader(type);
  
  const char *c_str = shaderSource.c_str();
  glShaderSource(shaderId, 1, &c_str, NULL);
  glCompileShader(shaderId);
  
  GLint params;
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &params);
  if(params == GL_FALSE) {
    char infoLog[512 + 1];
    int length = 512;
    glGetShaderInfoLog(shaderId, 500, &length, infoLog);
    std::cout << infoLog << std::endl;
    std::cout << "Could not compile shader." << std::endl;
    exit(-1);
  }
  
  return shaderId;
}
