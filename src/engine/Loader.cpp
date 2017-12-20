#include "Loader.h"

#include <iostream>

RawModel_ptr Loader::loadToVAO(unsigned int numIndices, unsigned int indices[],
                               unsigned int numPositions, float positions[],
                               unsigned int numTextCoords, float textureCoords[]) {
  VAO_ptr vao = createVAO();
  vao->addIndexAttribute(numIndices, indices);
  vao->addArrayAttribute(0, 3, numPositions, positions);
  vao->addArrayAttribute(1, 2, numTextCoords, textureCoords);
  vao->unbind_all();
  return std::make_shared<RawModel>(vao, numIndices);
}

RawModel_ptr Loader::loadToVAO(std::vector<GLuint> & indices,
                               std::vector<glm::vec3> & positions,
                               std::vector<glm::vec2> & textures){
  VAO_ptr vao = createVAO();
  vao->addIndexAttribute(indices);
  vao->addArrayAttribute(0, 3, positions);
  vao->addArrayAttribute(1, 2, textures);
  vao->unbind_all();
  return std::make_shared<RawModel>(vao, indices.size());
}

RawModel_ptr Loader::loadToVAO(std::vector<GLuint> & indices,
                               std::vector<glm::vec3> & positions,
                               std::vector<glm::vec2> & textures,
                               std::vector<glm::vec3> & normals){
  VAO_ptr vao = createVAO();
  vao->addIndexAttribute(indices);
  vao->addArrayAttribute(0, 3, positions);
  vao->addArrayAttribute(1, 2, textures);
  vao->addArrayAttribute(2, 3, normals);
  vao->unbind_all();
  return std::make_shared<RawModel>(vao, indices.size());
}



VAO_ptr Loader::createVAO() {
  VAO_ptr vao = std::make_shared<VAO>();
  vao->generate();
  vao->bind();
  _vaos.push_back(vao);
  return vao;
}


ModelTexture_ptr Loader::loadTexture(std::string fileName) {
  Texture_ptr texture = std::make_shared<sf::Texture>();
  
  if(!texture->loadFromFile(fileName)) {
    std::cout << "Could not load texture" << std::endl;
    exit(-1);
  }
    
  ModelTexture_ptr modelTexture = std::make_shared<ModelTexture>(texture, 1, 0);
  
  _textures.push_back(modelTexture);
  
  return modelTexture;
}

