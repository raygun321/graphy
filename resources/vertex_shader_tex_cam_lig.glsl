#version 400

//layout(location = 0) in vec3 position;

in vec3 position;
in vec2 textureCoords;
in vec3 normal;

out vec2 pass_textureCoords;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCameraVector;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition;

void main(void) {

	// Transform the Vertex position
	vec4 worldPosition = transformationMatrix * vec4(position, 1.0);
	
	// Apply the Camera
  gl_Position = projectionMatrix * viewMatrix * worldPosition;

	// Pass the texture
  pass_textureCoords = textureCoords;
  
  // Transform the Normal vector
  surfaceNormal = (transformationMatrix * vec4(normal, 0.0)).xyz;
  toLightVector = lightPosition - worldPosition.xyz;
  
  // Get Camera position from the View Matrix
  toCameraVector = (inverse(viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;
  
}