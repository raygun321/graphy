#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

class Util {
public:

    static glm::mat4 createTransformationMatrix(glm::vec3 &translation, glm::vec3 &rotation, float scale);
    static glm::mat4 createTransformationMatrix(glm::vec3 &translation, glm::vec3 &rotation, glm::vec3 &scale);
    static glm::mat4 createTransformationMatrix(glm::vec3 &translation, glm::quat &rotation, float scale);
    static glm::mat4 createTransformationMatrix(glm::vec3 &translation, glm::quat &rotation, glm::vec3 &scale);
    static glm::mat4 createViewMatrix(glm::vec3 &translation, glm::vec3 &rotation);
    static glm::vec3 toEulerAngle(const glm::quat& q);
    static glm::quat rotationBetweenVectors(glm::vec3 start, glm::vec3 dest);
    static void getRotation(const glm::mat4 &transMatrix, glm::vec3 & rotation);

private:
};

