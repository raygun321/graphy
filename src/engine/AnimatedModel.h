#pragma once

#include "Animator.h"
#include "Joint.h"
#include "VAO.h"
#include "Texture.h"

class AnimatedModel {
public:
  AnimatedModel(VAO_ptr model, Texture texture, Joint root, int jointCount);
  ~AnimatedModel();
  
  VAO_ptr getModel();
  
  Joint getRootJoint();
  
  void doAnimation(Animation animation)

  void update();

  glm::mat4[] getJointTransforms();
  
private:
  void addJointsToArray(Joint &root, glm::mat4[] &jointMatrices);

  VAO_ptr _model;
  Texture _texture;
  
  Joint _rootJoint;
  int _jointCount;
  
  Animator _animator;
};
