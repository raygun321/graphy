#pragma once

#include <memory>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/OpenGL.hpp>

typedef std::shared_ptr<sf::Texture> Texture_ptr;

class ModelTexture {
public:

  ModelTexture();  
  ModelTexture(Texture_ptr texture, GLfloat shineDamper, GLfloat reflectivity );
  ~ModelTexture();
  
  Texture_ptr getTexture() {return _texture; };
  void setTexture(Texture_ptr texture) {_texture = texture; };

  GLfloat getShineDamper() {return _shineDamper; };
  void setShineDamper(GLfloat damper) {_shineDamper = damper; };

  GLfloat getReflectivity() {return _reflectivity; };
  void setReflectivity(GLfloat reflectivity) {_reflectivity = reflectivity; };
  
private:
  Texture_ptr _texture;
  GLfloat _shineDamper;
  GLfloat _reflectivity;
};

typedef std::shared_ptr<ModelTexture> ModelTexture_ptr;

