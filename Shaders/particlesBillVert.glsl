#version 430 core


struct Particle {
	vec4 position;
	vec4 direction;
};

layout(std430, binding = 0) buffer particles
{
	Particle part[];
};

out float age;

void main()
{
	gl_Position = vec4(part[gl_VertexID].position.xyz, 1.0f);
	age = part[gl_VertexID].position.w;
}