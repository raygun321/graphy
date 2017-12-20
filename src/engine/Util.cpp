#include "Util.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/norm.hpp>

glm::mat4 Util::createTransformationMatrix(glm::vec3 &translation, glm::quat &rotation, float scale) {
  glm::mat4 tMatrix = glm::translate(glm::mat4(), translation);
  glm::mat4 sMatrix = glm::scale(glm::vec3(scale));
  glm::mat4 rMatrix = glm::toMat4(rotation);
  
  return tMatrix * rMatrix * sMatrix;
}

glm::mat4 Util::createTransformationMatrix(glm::vec3 &translation, glm::quat &rotation, glm::vec3 &scale) {
  glm::mat4 tMatrix = glm::translate(glm::mat4(), translation);
  glm::mat4 sMatrix = glm::scale(scale);
  glm::mat4 rMatrix = glm::toMat4(rotation);
  
  return tMatrix * rMatrix * sMatrix;
}


glm::mat4 Util::createTransformationMatrix(glm::vec3 &translation, glm::vec3 &rotation, float scale) {
  glm::mat4 tMatrix = glm::translate(glm::mat4(), translation);
  
  glm::mat4 sMatrix = glm::scale(glm::vec3(scale));
  
  glm::quat rQuat = glm::quat(rotation);
    glm::mat4 rMatrix = glm::toMat4(rQuat);
  
  return tMatrix * rMatrix * sMatrix;
}

glm::mat4 Util::createTransformationMatrix(glm::vec3 &translation, glm::vec3 &rotation, glm::vec3 &scale) {
  glm::mat4 tMatrix = glm::translate(glm::mat4(), translation);
  
  glm::mat4 sMatrix = glm::scale(scale);
  
  glm::quat rQuat = glm::quat(rotation);
    glm::mat4 rMatrix = glm::toMat4(rQuat);
  
  return tMatrix * rMatrix * sMatrix;
}


glm::mat4 Util::createViewMatrix(glm::vec3 &translation, glm::vec3 &rotation) {
  glm::vec3 reverseTranslation = glm::vec3(-translation[0], -translation[1], -translation[2]);
  glm::mat4 tMatrix = glm::translate(glm::mat4(), reverseTranslation);
  
  glm::quat rQuat = glm::quat(rotation);
  glm::mat4 rMatrix = glm::toMat4(rQuat);
  
  return rMatrix * tMatrix;
}

glm::vec3 Util::toEulerAngle(const glm::quat& q) {
	return glm::eulerAngles(q); // pitch, yaw, roll
}


/*
mat4 Util::getIdentityMatrix() {
  return glm::mat4(1.0f);
}
*/

glm::quat Util::rotationBetweenVectors(glm::vec3 start, glm::vec3 dest){
	start = glm::normalize(start);
	dest = glm::normalize(dest);

	float cosTheta = glm::dot(start, dest);
	glm::vec3 rotationAxis;

	if (cosTheta < -1 + 0.001f){
		// special case when vectors in opposite directions:
		// there is no "ideal" rotation axis
		// So guess one; any will do as long as it's perpendicular to start
        rotationAxis = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), start);
        if (glm::length2(rotationAxis) < 0.01 ) // bad luck, they were parallel, try again!
            rotationAxis = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), start);

		rotationAxis = glm::normalize(rotationAxis);
        return glm::angleAxis(glm::radians(180.0f), rotationAxis);
	}

	rotationAxis = glm::cross(start, dest);

	float s = sqrt( (1+cosTheta)*2 );
	float invs = 1 / s;

	return glm::quat(
		s * 0.5f, 
		rotationAxis.x * invs,
		rotationAxis.y * invs,
		rotationAxis.z * invs);
}

void Util::getRotation(const glm::mat4 &transMatrix, glm::vec3 & rotation)
{
    glm::quat q(transMatrix);
    float yaw = glm::yaw(q);
    float pitch = glm::pitch(q);
    float roll = glm::roll(q);

    rotation.x = pitch;
    rotation.y = yaw;
    rotation.z = roll;
}
