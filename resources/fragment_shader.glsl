#version 400

in vec2 pass_textureCoords;
//in vec4 pass_color;

out vec4 out_color;

uniform sampler2D textureSampler;

void main(void) {
//  out_color = vec4(pass_color);
  out_color = texture(textureSampler, pass_textureCoords);
}