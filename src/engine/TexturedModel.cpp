#include "TexturedModel.h"

TexturedModel::TexturedModel(RawModel_ptr model, Texture_ptr texture) {
  _model = model;
  _texture = texture;
}
  
TexturedModel::~TexturedModel() {
}

RawModel_ptr TexturedModel::getModel() {
  return _model;
}

void TexturedModel::setModel(RawModel_ptr model) {
  _model = model;
}

Texture_ptr TexturedModel::getTexture() {
  return _texture;
}

void TexturedModel::setTexture(Texture_ptr texture) {
 _texture = texture;
}
