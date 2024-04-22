#version 440 core

layout(location = 0) in vec3 aPos;


uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{

	vec4 worldSpace = Model * vec4(aPos, 1.0);
	gl_Position = Projection * View * worldSpace;

}