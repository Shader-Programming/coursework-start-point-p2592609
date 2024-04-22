#version 410 core

///////////////////////// INS OUTS
out vec4 FragColor;

in vec2 UV;
//in vec3 gNormal;
in vec3 PosInWS;

uniform sampler2D image;

void main()
{
	vec3 result = texture(image, UV).rgb;
	FragColor = vec4(result, 1.0);
	//FragColor = vec4(0.1f, 45.0f, 1.0f, 1.0f);
}