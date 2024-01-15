#version 330
layout(location = 0) in vec3 aPos;

out vec3 texCoords;

uniform mat4 projectionView;


void main()
{
	texCoords = aPos;
	gl_Position = projectionView * vec4(aPos, 1.0);
}