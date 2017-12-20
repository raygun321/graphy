#include "Light.h"

Light::Light(const glm::vec3 &position,
             const glm::vec3 &color) {
    _position = position;
    _color = color;
}

Light::~Light() {}
