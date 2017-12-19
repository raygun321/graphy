#pragma once

#include "RawModel.h"
#include "Texture.h"
#include <memory>

class TexturedModel {
public:

  TexturedModel(RawModel_ptr, Texture_ptr);
  
  ~TexturedModel();
  
  RawModel_ptr getModel();
  void setModel(RawModel_ptr);

  Texture_ptr getTexture();
  void setTexture(Texture_ptr);
  
private:
  RawModel_ptr _model;
  Texture_ptr _texture;
};

typedef std::shared_ptr<TexturedModel> TexturedModel_ptr;

