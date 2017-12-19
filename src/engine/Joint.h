#pragma once

#include <vector>
#include <string>

#include <glm/mat4x4.hpp> // glm::mat4

class Joint {
public:
  Joint(int id, 
        const std::string &name,
        const glm::mat4 &transform);

  ~Joint();
  
  void addChild(Joint &child);
  
  glm::mat4 getAnimatedTransform();
  void setAnimatedTransform(glm::mat4 transform);
  
  glm::mat4 getInverseBindTransform();
  
  void calcInverseBindTransform(const glm::mat4 &parentBindTransform);

  int index;
  std::string name;
  std::vector<Joint *> children;
private:
  
  // TODO: Use double quaternions
  glm::mat4 _animatedTransform;
  
  // Original Pose
  glm::mat4 _localBindTransform;
  // 
  glm::mat4 _inverseBindTransform;
};
