#version 410 core

in vec2 uv;

uniform sampler2D billboard;
out vec4 FragColour;

float threshold = 0.35;

void main()
{
	FragColour = texture(billboard, uv);

	if (FragColour.r > threshold &&
		FragColour.g > threshold &&
		FragColour.b > threshold)
	{
		discard;
	}
}