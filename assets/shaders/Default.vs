#version 400

uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
//uniform mat4 ViewInverse;
uniform mat4 ModelMatrix;

in vec4 vertex;
in vec2 vertexTexture;

out vec2 texture;

void main () 
{
  gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vertex;
  texture = vec2(vertexTexture.x, -vertexTexture.y);
};