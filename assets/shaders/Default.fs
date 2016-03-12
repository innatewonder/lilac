#version 400

uniform vec4 stripColor;

out vec4 frag_colour;

void main () 
{
  frag_colour = stripColor;
};
