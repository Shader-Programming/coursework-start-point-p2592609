#version 410 core

in vec2 uv;

uniform smapler2D billboard;
out vec4 FragColour;

float threshold = 0.35;

void main()
{
	FragColour = texture(billboard, uv);

	if(FragColour.r)
}