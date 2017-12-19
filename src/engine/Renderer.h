#pragma once

#include "Entity.h"
#include "ShaderProgram.h"
#include <glm/mat4x4.hpp>
#include <memory>

class Renderer {
public:
  Renderer(float aspectRatio, GLuint location, ShaderProgram_ptr shader);
  
  void prepare();
  
  void render(Entity_ptr entity, GLuint location, ShaderProgram_ptr shader);
  
private:
  void createProjectionMatrix(float aspectRatio);

  glm::mat4 _projectionMatrix;
  
  static float FOV;
  static float NEAR_PLANE;
  static float FAR_PLANE;
};

typedef std::shared_ptr<Renderer> Renderer_ptr;