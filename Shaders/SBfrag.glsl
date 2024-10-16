#version 330
out vec4 FragColour;
in vec3 texCoords;

uniform samplerCube skybox;

void main()
{
	FragColour = texture(skybox, texCoords);
}