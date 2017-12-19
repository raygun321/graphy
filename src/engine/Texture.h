#pragma once

#include <memory>

#include <SFML/Graphics/Texture.hpp>

/*
class Texture {
public:

  Texture();  
  ~Texture();
  
  void generate();
  
  void bind();
  
  void uploadData();
  
  void setType(GLenum type);
  
private:
  GLuint _id;
  State _state;
  GLenum _type;
};
*/

typedef std::shared_ptr<sf::Texture> Texture_ptr;
//typedef std::shared_ptr<Texture> Texture_ptr;
