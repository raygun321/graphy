#include "StaticShader.h"

#include "config.h"

std::string StaticShader::makeString(const char * str1, const char * str2) {
    std::string temp = str1;
    temp += str2;
    return temp;
}

std::string StaticShader::VERTEX_FILE = makeString(graphy_RESOURCE_PATH, "/resources/vertex_shader.glsl");
std::string StaticShader::FRAGMENT_FILE = makeString(graphy_RESOURCE_PATH, "/resources/fragment_shader.glsl");

StaticShader::StaticShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE) {
}
  
void StaticShader::bindAttributes() {
  bindAttribute(0, "position");
  bindAttribute(1, "textureCoords");
}

void StaticShader::getAllUniformLocations() {
  _transformationMatrixLocation = getUniformLocation("transformationMatrix");
  _projectionMatrixLocation = getUniformLocation("projectionMatrix");
  _viewMatrixLocation = getUniformLocation("viewMatrix");
}

void StaticShader::loadTransformationMatrix(glm::mat4 matrix) {
  loadUniform(_transformationMatrixLocation, matrix);
}

void StaticShader::loadProjectionMatrix(glm::mat4 matrix) {
  loadUniform(_projectionMatrixLocation, matrix);
}

void StaticShader::loadViewMatrix(Camera_ptr camera) {
  loadUniform(_viewMatrixLocation, camera->getViewMatrix());
}
