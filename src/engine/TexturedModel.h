#pragma once

#include "RawModel.h"
#include "ModelTexture.h"
#include <memory>

class TexturedModel {
public:

  TexturedModel(RawModel_ptr, ModelTexture_ptr);
  
  ~TexturedModel();
  
  RawModel_ptr getModel();
  void setModel(RawModel_ptr);

  ModelTexture_ptr getModelTexture();
  void setModelTexture(ModelTexture_ptr);
  
private:
  RawModel_ptr _model;
  ModelTexture_ptr _modelTexture;
};

typedef std::shared_ptr<TexturedModel> TexturedModel_ptr;

