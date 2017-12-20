#pragma once

#include <glm/vec3.hpp>
#include <memory>

class Light {
public:
    Light(const glm::vec3 &position,
          const glm::vec3 &color);
    ~Light();
    
    const glm::vec3 & getPosition() { return _position; };
    void setPosition(const glm::vec3 &pos) { _position = pos; };

    const glm::vec3 & getColor() { return _color; };
    void setColor(const glm::vec3 &color) { _color = color; };

private:
    glm::vec3 _position;
    glm::vec3 _color;
};

typedef std::shared_ptr<Light> Light_ptr;

