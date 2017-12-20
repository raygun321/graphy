#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>

float Renderer::FOV = 70; //* M_PI / 180.0;
float Renderer::NEAR_PLANE = 0.1f;
float Renderer::FAR_PLANE = 1000.f;

Renderer::Renderer(float aspectRatio, GLuint location, ShaderProgram_ptr shader) {
  createProjectionMatrix(aspectRatio);
  shader->start();
  shader->loadUniform(location, _projectionMatrix);
  shader->stop();
}

void Renderer::prepare() {
  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //glClearColor(0, 0, 0, 1);
}

void Renderer::render(Entity_ptr entity, ShaderProgram_ptr shader) {
  TexturedModel_ptr model = entity->getModel();
  RawModel_ptr raw = model->getModel();
  ModelTexture_ptr modelTexture = model->getModelTexture();
  Texture_ptr texture = modelTexture->getTexture();
    
  sf::Texture::bind(&(*texture));
    
  VAO_ptr vao = raw->getVAO();
  vao->enable();
  shader->loadTransformationMatrix(entity->getTranslationMatrix());
  shader->loadShineVariables(modelTexture->getShineDamper(), modelTexture->getReflectivity());

  glDrawElements(GL_TRIANGLES, raw->getVertexCount(), GL_UNSIGNED_INT, 0);
    
  if(glGetError() != GL_NO_ERROR) {
    //TODO: Handle Error
  }

  sf::Texture::bind(NULL);
    
  vao->disable_all();
  vao->unbind_all();

}

void Renderer::createProjectionMatrix(float aspectRatio) {
  _projectionMatrix = glm::perspective(glm::radians(FOV), aspectRatio, NEAR_PLANE, FAR_PLANE);
/*
  float x_scale = (1f / tan(FOV / 2f));
  float y_scale = x_scale*aspectRatio;
  float frustrum_length = FAR_PLANE - NEAR_PLANE;
  
  _projection_matrix[0][0] = x_scale;
  _projection_matrix[1][1] = y_scale;
  _projection_matrix[2][2] = -((FAR_PLANE + NEAR_PLANE) / frustrum_length);
  _projection_matrix[2][3] = -1;
  _projection_matrix[3][2] = -((2*NEAR_PLANE*FAR_PLANE) / frustrum_length);
  _projection_matrix[3][3] = 0; 
*/
}
