#include "AnimatedModel.h"

#include <algorithm>

#include <glm/mat4x4.hpp>

AnimatedModel::AnimatedModel(VAO_ptr model, Texture texture, Joint root, int jointCount) :
  _model(model),
  _texture(texture),
  _rootJoint(root),
  _jointCount(jointCount) {
  _animator = new Animator(this);
  _rootJoint.calcInverseBindTransform(glm::mat4());
}

AnimatedModel::~AnimatedModel() {
  _model.delete();
  _texture.delete();
}

VAO_ptr AnimatedModel::getModel() {
  return _model;
}

Joint AnimatedModel::getRootJoint() {
  return _rootJoint;
}

void AnimatedModel::doAnimation(Animation animation) {
  _animator.doAnimation(animation);
}

void AnimatedModel::update() {
  _animator.update();
}

glm::mat4[] AnimatedModel::getJointTransforms() {
  glm::mat4[] jointMatrices = new glm::mat4[_jointCount];
  addJointsToArray(rootJoint, jointMatrices);
  return jointMatrices;
}

void AnimatedModel::addJointsToArray(Joint &headJoint, glm::mat4[] &jointMatrices) {
  jointMatrices[headJoint.index] = headJoint.getAnimatedTransform();
  std::for_each(headJoint.children.begin(), 
                headJoint.children.end(), 
                [](Joint *j) {addJointsToArray(*j, jointMatrices); } );

}
