#include "FlatTextureShader.h"


#include "config.h"

std::string FlatTextureShader::makeString(const char * str1, const char * str2) {
    std::string temp = str1;
    temp += str2;
    return temp;
}

std::string FlatTextureShader::VERTEX_FILE = makeString(graphy_RESOURCE_PATH, "/resources/vertex_shader_tex_cam.glsl");
std::string FlatTextureShader::FRAGMENT_FILE = makeString(graphy_RESOURCE_PATH, "/resources/fragment_shader_tex.glsl");

FlatTextureShader::FlatTextureShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE) {
}
  
void FlatTextureShader::bindAttributes() {
  bindAttribute(0, "position");
  bindAttribute(1, "textureCoords");
}

void FlatTextureShader::getAllUniformLocations() {
  _transformationMatrixLocation = getUniformLocation("transformationMatrix");
  _projectionMatrixLocation = getUniformLocation("projectionMatrix");
  _viewMatrixLocation = getUniformLocation("viewMatrix");
}

void FlatTextureShader::loadTransformationMatrix(glm::mat4 matrix) {
  loadUniform(_transformationMatrixLocation, matrix);
}

void FlatTextureShader::loadProjectionMatrix(glm::mat4 matrix) {
  loadUniform(_projectionMatrixLocation, matrix);
}

void FlatTextureShader::loadViewMatrix(Camera_ptr camera) {
  loadUniform(_viewMatrixLocation, camera->getViewMatrix());
}
