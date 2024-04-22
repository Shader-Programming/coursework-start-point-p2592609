#version 330 core

in vec2 uv;

out vec4 FragColor;

uniform sampler2D defaultTexture;



void main()
{
	vec3 result = texture(defaultTexture, uv).rgb;
	FragColor = vec4(result, 1.0);
}