#pragma once

#include <memory>
#include <string>
#include "ShaderProgram.h"
#include "Camera.h"
#include "Light.h"

class StaticShader : public ShaderProgram {
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
  
  void loadLight(Light_ptr light);
  GLuint getLightPositionLocation() { return _lightPositionLocation; };
  GLuint getLightColorLocation() { return _lightColorLocation; };

  void loadShineVariables(GLfloat damper, GLfloat reflectivity);
  GLuint getShineDamperLocation() { return _shineDamperLocation; };
  GLuint getReflectivityLocation() { return _reflectivityLocation; };  

private:
  static std::string VERTEX_FILE;
  static std::string FRAGMENT_FILE;
  static std::string makeString(const char * str1, const char * str2);

  GLuint _transformationMatrixLocation;
  GLuint _projectionMatrixLocation;
  GLuint _viewMatrixLocation;
  GLuint _lightPositionLocation;
  GLuint _lightColorLocation;
  GLuint _shineDamperLocation;
  GLuint _reflectivityLocation;
};

typedef std::shared_ptr<StaticShader> StaticShader_ptr;
