#include "Joint.h"

#include <algorithm>

#include <glm/gtc/matrix_inverse.hpp>

Joint::Joint(int id, 
             const std::string &name, 
             const glm::mat4 &transform) :
  index(id),
  name(name),
  _localBindTransform(transform) {
  
}

Joint::~Joint() {}

void Joint::addChild(Joint &child) {
  children.push_back(&child);
}

glm::mat4 Joint::getAnimatedTransform() {
  return _animatedTransform;
}

void Joint::setAnimatedTransform(glm::mat4 transform) {
  _animatedTransform = transform;
}
  
/* Inverted model-space bind transform */
glm::mat4 Joint::getInverseBindTransform() {
  return _inverseBindTransform;
}

void Joint::calcInverseBindTransform(const glm::mat4 &parentBindTransform) {
  glm::mat4 bindTransform = parentBindTransform * _localBindTransform;
  _inverseBindTransform = glm::inverse(bindTransform);
  std::for_each(children.begin(), children.end(), [](Joint *j) {j->calInverseBindTransform(bindTransform);} );
}
