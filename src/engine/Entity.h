#pragma once

#include "TexturedModel.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <memory>

class Entity {
public:
  Entity(TexturedModel_ptr model,
         glm::vec3 position,
         glm::vec3 rotation,
         float scale);

  Entity(TexturedModel_ptr model,
         glm::vec3 position,
         glm::quat rotation,
         float scale);
      
  Entity(TexturedModel_ptr model,
         glm::vec3 position,
         glm::vec3 rotation,
         glm::vec3 scale);

  Entity(TexturedModel_ptr model,
         glm::vec3 position,
         glm::quat rotation,
         glm::vec3 scale);

  ~Entity();
  
  void increasePosition(float dx, float dy, float dz);
  void increaseRotation(float dx, float dy, float dz);
  void increaseScale(float delta);
  
  TexturedModel_ptr getModel() { return _model; };
  void setModel(TexturedModel_ptr model) { _model = model; };
  
  glm::vec3 getPosition() { return _position; };
  void setPosition(glm::vec3 pos) { _position = pos; _dirtyMatrix = true; };
  
  glm::quat getRotation() { return _rotation; };
  void setRotation(glm::vec3 rot) { _rotation = glm::quat(rot); _dirtyMatrix = true; };
  void setRotation(glm::quat rot) { _rotation = rot; _dirtyMatrix = true; };
  
  glm::vec3 getScale() { return _scale; };
  void setScale(float scale) { _scale.x = scale; _scale.y = scale; _scale.z = scale; _dirtyMatrix = true; };
  void setScale(glm::vec3 scale) { _scale = scale; _dirtyMatrix = true; };
  
  glm::mat4 getTranslationMatrix();
private:
  TexturedModel_ptr _model;
  glm::vec3 _position;
  glm::quat _rotation;
  glm::vec3 _scale;
  glm::mat4 _translationMatrix;
  bool _dirtyMatrix;
  bool _simpleScale;
};

typedef std::shared_ptr<Entity> Entity_ptr;

