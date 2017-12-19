#include "Entity.h"
#include "Util.h"

Entity::Entity(TexturedModel_ptr model,
               glm::vec3 position,
               glm::quat rotation,
               float scale) {
  _model = model;
  _position = position;
  _rotation = rotation;
  _scale.x = scale;
  _scale.y = scale;
  _scale.z = scale;
  _translationMatrix = Util::createTransformationMatrix(position, rotation, scale);
  _dirtyMatrix = false;
}

Entity::Entity(TexturedModel_ptr model,
               glm::vec3 position,
               glm::vec3 rotation,
               float scale) {
  _model = model;
  _position = position;
  _rotation = glm::quat(rotation);
  _scale.x = scale;
  _scale.y = scale;
  _scale.z = scale;
  _translationMatrix = Util::createTransformationMatrix(position, rotation, scale);
  _dirtyMatrix = false;
}

Entity::Entity(TexturedModel_ptr model,
               glm::vec3 position,
               glm::vec3 rotation,
               glm::vec3 scale) {
  _model = model;
  _position = position;
  _rotation = glm::quat(rotation);
  _scale = scale;
  _translationMatrix = Util::createTransformationMatrix(position, rotation, scale);
  _dirtyMatrix = false;
}

Entity::Entity(TexturedModel_ptr model,
               glm::vec3 position,
               glm::quat rotation,
               glm::vec3 scale) {
  _model = model;
  _position = position;
  _rotation = rotation;
  _scale = scale;
  _translationMatrix = Util::createTransformationMatrix(position, rotation, scale);
  _dirtyMatrix = false;
}

Entity::~Entity() {
}
  
  
glm::mat4 Entity::getTranslationMatrix() {
  if(_dirtyMatrix) {
    _translationMatrix = Util::createTransformationMatrix(_position, _rotation, _scale);
    _dirtyMatrix = false;
  }
  return _translationMatrix;
}

void Entity::increasePosition(float dx, float dy, float dz) {
  _dirtyMatrix = true;
  _position[0] += dx;
  _position[1] += dy;
  _position[2] += dz;
}

void Entity::increaseRotation(float dx, float dy, float dz) {
    _dirtyMatrix = true;
    _rotation[0] += dx;
    _rotation[1] += dy;
    _rotation[2] += dz;
}

void Entity::increaseScale(float delta) {
    _dirtyMatrix = true;
    _scale += delta;
}
