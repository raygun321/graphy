#pragma once

#include <memory>
#include <string>
#include "ShaderProgram.h"
#include "Camera.h"


class FlatTextureShader : public FlatTextureShader {
public:
  StaticShader();
  
  void bindAttributes();
  void getAllUniformLocations();
  
  void loadTransformationMatrix(glm::mat4 matrix);
  GLuint getTransformationMatrixLocation() { return _transformationMatrixLocation; };
  
  void loadProjectionMatrix(glm::mat4 matrix);
  GLuint getProjectionMatrixLocation() { return _projectionMatrixLocation; };
  
  void loadViewMatrix(Camera_ptr camera);
  GLuint getViewMatrixLocation() { return _viewMatrixLocation; };
  
  void loadLight(Light_ptr light) {};
  void loadShineVariables(GLfloat damper, GLfloat reflectivity) {};

private:
  static std::string VERTEX_FILE;
  static std::string FRAGMENT_FILE;
  static std::string makeString(const char * str1, const char * str2);

  GLuint _transformationMatrixLocation;
  GLuint _projectionMatrixLocation;
  GLuint _viewMatrixLocation;
  
};

typedef std::shared_ptr<FlatTextureShader> FlatTextureShader_ptr;
