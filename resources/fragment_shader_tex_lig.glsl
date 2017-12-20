#version 400

in vec2 pass_textureCoords;
in vec3 surfaceNormal;
in vec3 toLightVector;
in vec3 toCameraVector;

out vec4 out_color;

uniform sampler2D textureSampler;
uniform vec3 lightColor;
uniform float shineDamper;
uniform float reflectivity;

void main(void) {
  vec3 unitNormal = normalize(surfaceNormal);
  vec3 unitLightVector = normalize(toLightVector);
  
  // Diffuse Lighting
  float nDotl = dot(unitNormal, unitLightVector);
  float brightness = max(nDotl, 0.0); // Limit to 0 minimum
  vec3 diffuseColor = brightness * lightColor;
  
  // Specular Lighting
  vec3 unitVectorToCamera = normalize(toCameraVector);
  vec3 lightDirection = -unitLightVector;
  vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);
  float specularFactor = dot(reflectedLightDirection, unitVectorToCamera);
  specularFactor = max(specularFactor, 0.0);
  float dampedFactor = pow(specularFactor, shineDamper);
  vec3 finalSpecular = dampedFactor * reflectivity * lightColor;
  
  out_color = vec4(diffuseColor, 1.0) * texture(textureSampler, pass_textureCoords) + vec4(finalSpecular, 1.0);
}