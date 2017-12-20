#include "TexturedModel.h"

TexturedModel::TexturedModel(RawModel_ptr model, ModelTexture_ptr texture) {
  _model = model;
  _modelTexture = texture;
}
  
TexturedModel::~TexturedModel() {
}

RawModel_ptr TexturedModel::getModel() {
  return _model;
}

void TexturedModel::setModel(RawModel_ptr model) {
  _model = model;
}

ModelTexture_ptr TexturedModel::getModelTexture() {
  return _modelTexture;
}

void TexturedModel::setModelTexture(ModelTexture_ptr texture) {
 _modelTexture = texture;
}
