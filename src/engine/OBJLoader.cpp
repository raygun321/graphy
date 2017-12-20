#include "OBJLoader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>
#include <glm/gtx/hash.hpp>

#include <unordered_map>

RawModel_ptr OBJLoader::loadObjModel(std::string fileName, Loader & loader) {
  std::vector<GLuint> vertexIdx, textureIdx, normalIdx, indices;
  std::vector<glm::vec3> temp_vertices;
  std::vector<glm::vec2> temp_textures;
  std::vector<glm::vec3> temp_normals;

  std::vector < glm::vec3 > out_vertices;
  std::vector < glm::vec2 > out_textures;
  std::vector < glm::vec3 > out_normals;
  
  std::ifstream fileStream;    
  fileStream.open(fileName);
  if(!fileStream.is_open()) {
    std::cout << "Could not open file." << std::endl;
    exit(-1);
  }
  
  while( 1 ) {
    std::string line;
    
    std::getline(fileStream, line);
    if(fileStream.eof()) {
      break;
    }
    
    std::istringstream iss(line);
    std::string lineType; 
    
    iss >> lineType;
    if(lineType.compare("v") ==0) {
      glm::vec3 vertex;
      iss >> vertex.x >> vertex.y >> vertex.z;
      temp_vertices.push_back(vertex);
    } else if(lineType.compare("vt") ==0) {
      glm::vec2 uv;
      iss >> uv.x >> uv.y;
      uv.y = 1-uv.y;
      temp_textures.push_back(uv);
    } else if(lineType.compare("vn") ==0) {
      glm::vec3 normal;
      iss >> normal.x >> normal.y >> normal.z;
      temp_normals.push_back(normal);
    } else if(lineType.compare("f") ==0) {
      std::string vertex1, vertex2, vertex3;
      char filler;
      unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
      if(!( iss >> vertexIndex[0] >> filler >> uvIndex[0] >> filler >> normalIndex[0]
         && iss >> vertexIndex[1] >> filler >> uvIndex[1] >> filler >> normalIndex[1]
         && iss >> vertexIndex[2] >> filler >> uvIndex[2] >> filler >> normalIndex[2])) {
        std::cout << "File can't be read by our simple parser : ( Try exporting with other options" << std::endl;
        exit(-1);
      }
      
      vertexIdx. push_back(vertexIndex[0] - 1);
      vertexIdx. push_back(vertexIndex[1] - 1);
      vertexIdx. push_back(vertexIndex[2] - 1);
      textureIdx.push_back(uvIndex[0] - 1);
      textureIdx.push_back(uvIndex[1] - 1);
      textureIdx.push_back(uvIndex[2] - 1);
      normalIdx. push_back(normalIndex[0] - 1);
      normalIdx. push_back(normalIndex[1] - 1);
      normalIdx. push_back(normalIndex[2] - 1);
    }
  }
  
  std::unordered_map<glm::mat3x3, GLuint> vertexMap;
  GLuint next_idx = 0;
  GLuint cur_idx = 0;
  for( unsigned int i = 0; i < vertexIdx.size(); ++i) {
    bool newIndex = true;
    
    unsigned int vertexIndex = vertexIdx[i];
    glm::vec3 vertex = temp_vertices[ vertexIndex ];

    unsigned int textureIndex = textureIdx[i];   
    glm::vec2 texture = temp_textures[ textureIndex ];

    unsigned int normalIndex = normalIdx[i];   
    glm::vec3 normal = temp_normals[ normalIndex ];
    
    glm::mat3x3 key(vertex.x, vertex.y, vertex.z,
                    texture.x, texture.y, 0,
                    normal.x, normal.y, normal.z);
    
    if(vertexMap.find(key) != vertexMap.end() ) {
      cur_idx = vertexMap[key];
      newIndex = false;
    }
    
    if(newIndex) {
      out_vertices.push_back(vertex);
      out_textures.push_back(texture);
      out_normals.push_back(normal);
      
      cur_idx = next_idx++;
      vertexMap[key] = cur_idx;
    }
    indices.push_back(cur_idx);
	}
	
	return loader.loadToVAO(indices,out_vertices,out_textures, out_normals);
}

