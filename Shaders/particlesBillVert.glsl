#version 330 core
layout(location = 0) in vec4 aPos;

out float age

void main()
{
	gl_Position = vec4(aPos.xyz, 1.0);
	age = aPos.w;
}