////////////////////////////////////////////////////////////////////////////////
// Filename: light.ps
////////////////////////////////////////////////////////////////////////////////
#version 400


/////////////////////
// INPUT VARIABLES //
/////////////////////
in vec2 texCoord;
in vec3 normal;


//////////////////////
// OUTPUT VARIABLES //
//////////////////////
out vec4 outputColor;
//First we add a 4 float ambient light uniform variable so that the ambient light color can be set //in this shader by outside classes.

///////////////////////
// UNIFORM VARIABLES //
///////////////////////
uniform sampler2D shaderTexture;
uniform vec3 lightDirection;
uniform vec4 diffuseLightColor;
uniform vec4 ambientLight;


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
void main(void)
{
  vec4 textureColor;
  vec4 color;
  vec3 lightDir;
  float lightIntensity;


  // Sample the pixel color from the texture using the sampler at this texture coordinate location.
  textureColor = texture(shaderTexture, texCoord);
//We set the output color value to the base ambient color. All pixels will now be illuminated by a minimum of the ambient color value.

  // Set the default output color to the ambient light value for all pixels.
  color = ambientLight;

  // Invert the light direction for calculations.
  lightDir = -lightDirection;

  // Calculate the amount of light on this pixel.
  lightIntensity = clamp(dot(normal, lightDir), 0.0f, 1.0f);
//Check if the N dot L is greater than zero. If it is then add the diffuse color to the ambient color. If not then you need to be careful to not add the diffuse color. The reason being is that the diffuse color could be negative and it will subtract away some of the ambient color in the addition which is not correct.

  if(lightIntensity > 0.0f)
  {
    // Determine the final diffuse color based on the diffuse color and the amount of light intensity.
    color += (diffuseLightColor * lightIntensity);
  }
//Make sure to clamp the final output light color since the combination of ambient and diffuse could have been greater than 1.

  // Clamp the final light color.
  color = clamp(color, 0.0f, 1.0f);
//Finally combine the ambient/diffuse light to the texture pixel to produce the final result.

  // Multiply the texture pixel and the final diffuse color to get the final pixel color result.
  outputColor = color * textureColor;
}