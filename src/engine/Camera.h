#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <memory>

class Camera {
public:
  Camera();

  Camera(glm::vec3 position,
         glm::vec3 rotation);

  ~Camera();
  
  void increasePosition(float dx, float dy, float dz);
  void increaseRotation(float dx, float dy, float dz);
    
  glm::vec3 getPosition() { return _position; };
  void setPosition(glm::vec3 pos) { _position = pos; _dirtyMatrix = true; };
  
  glm::vec3 getRotation() { return _rotation; };
  void setRotation(glm::vec3 rot) { _rotation = rot; _dirtyMatrix = true; };
    
  glm::mat4 getViewMatrix();
    
  void lookAt(const glm::vec3 &position);
private:
  glm::vec3 _position;
  glm::vec3 _rotation;
  glm::vec3 _up;
  glm::mat4 _viewMatrix;
  bool _dirtyMatrix;
};

typedef std::shared_ptr<Camera> Camera_ptr;

