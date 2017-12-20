#include "ModelTexture.h"

#pragma once

ModelTexture::ModelTexture() {
  _shineDamper = 1;
  _reflectivity = 0;
}

ModelTexture::ModelTexture(Texture_ptr texture,GLfloat shineDamper, GLfloat reflectivity ){
  _texture = texture;
  _shineDamper = shineDamper;
  _reflectivity = reflectivity;
}


ModelTexture::~ModelTexture() {}

/*
Texture::Texture() {
  _state = State::UNSET;
  _id = 0;
  _type = GL_TEXTURE_2D;
}

Texture::~Texture() {
  if(_state != State::UNSET) {
    //TODO: Delete texture
    glDeleteTextures(&_id);
    
    if(glGetError() != GL_NO_ERROR) {
      //TODO: Handle Error
    }
  }
}

Texture::init() {
	glEnable(GL_TEXTURE2D);
}

void Texture::generate() {
  glGenTextures(1, &_id);

  if(glGetError() != GL_NO_ERROR) {
    //TODO: Handle Error
  }
  
  _state = State::CREATED;
}
  
void Texture::bind() {
  if(_state == State::UNSET) {
    generate();
  }
  
  glBindTexture(_type, &_id)

  if(glGetError() != GL_NO_ERROR) {
    //TODO: Handle Error
  }
  
  _state = State::BOUND;
}
  
void Texture::uploadData(const sf::Image & image) {
  if(_state != State::BOUND) {
    bind();
  }
  
  //TODO: Switch based on type?
  glTexImage2D(_type, 0, GL_RGBA, image.GetWidth(), image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.GetPixelsPtr());
  
  glTexParameteri(_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(_type, GL_TEXTURE_WRAP_T, GL_REPEAT);
}
  

void Texture::setType(GLenum type) {
  _type = type; 
}
*/
