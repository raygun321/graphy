#pragma once

#include "VAO.h"
#include "RawModel.h"
#include "ModelTexture.h"

#include <vector>
#include <string>

class Loader {
public:

  RawModel_ptr loadToVAO(unsigned int numIndices, unsigned int indices[],
                         unsigned int numPositions, float positions[],
                         unsigned int numTextCoords, float textureCoords[]);

  RawModel_ptr loadToVAO(std::vector<GLuint> & indices,
                         std::vector<glm::vec3> & positions,
                         std::vector<glm::vec2> & textures);
  
  RawModel_ptr loadToVAO(std::vector<GLuint> & indices,
                               std::vector<glm::vec3> & positions,
                               std::vector<glm::vec2> & textures,
                               std::vector<glm::vec3> & normals);
  
  ModelTexture_ptr loadTexture(std::string fileName);

private:
  std::vector<VAO_ptr> _vaos;
  std::vector<ModelTexture_ptr> _textures;
  
  VAO_ptr createVAO();

};
