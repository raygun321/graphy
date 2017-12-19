#include "Camera.h"
#include "Util.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {
  _position = glm::vec3(0,0,0);
  _rotation = glm::vec3(0,0,0);
  _up = glm::vec3(0,1,0);
  _viewMatrix = Util::createViewMatrix(_position, _rotation);
  _dirtyMatrix = false;
}

Camera::Camera(glm::vec3 position,
               glm::vec3 rotation) {
  _position = position;
  _rotation = rotation;
  _up = glm::vec3(0,1,0);
  _viewMatrix = Util::createViewMatrix(_position, _rotation);
  _dirtyMatrix = false;
}

Camera::~Camera() {
}
  
  
glm::mat4 Camera::getViewMatrix() {
  if(_dirtyMatrix) {
    _viewMatrix = Util::createViewMatrix(_position, _rotation);
    _dirtyMatrix = false;
  }
  return _viewMatrix;
}

void Camera::increasePosition(float dx, float dy, float dz) {
  _dirtyMatrix = true;
  _position[0] += dx;
  _position[1] += dy;
  _position[2] += dz;
}

void Camera::increaseRotation(float dx, float dy, float dz) {
  _dirtyMatrix = true;
  _rotation[0] += dx;
  _rotation[1] += dy;
  _rotation[2] += dz;
}

void Camera::lookAt(const glm::vec3 &targetPosition) {
    glm::mat4 matrix = glm::lookAt(_position, targetPosition, _up);
    Util::getRotation(matrix, _rotation);
    _dirtyMatrix = true;
}

