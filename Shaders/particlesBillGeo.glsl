#version 330 core
layout(points) in;
layout(triangle_strip, max_vertices = 4) out;
out vec2 uv;
out float ageGS;

in float age[];

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 cameraPos;
uniform int scale;

void main()
{
	ageGS = age[0];
	mat4 VP = projection * view;
	vec3 pos = gl_in[0].gl_Position.xyz;
	vec3 toCamera = normalize(cameraPos - pos);
	vec3 up = vec3(0.0, 1.0, 0.0);
	vec3 right = cross(toCamera, up);

	gl_Position = VP * vec4(pos, 1.0);
	uv = vec2(0.0, 0.0);
	EmitVertex();

	pos.y += 1.0 * scale;
	gl_Position = VP * vec4(pos, 1.0);
	uv = vec2(0.0, 1.0);
	EmitVertex();

	pos.y -= 1.0 * scale;
	pos += right * scale;
	gl_Position = VP * vec4(pos, 1.0);
	uv = vec2(1.0, 0.0);
	EmitVertex();

	pos.y += 1.0 * scale;
	gl_Position = VP * vec4(pos, 1.0);
	uv = vec2(1.0, 1.0);
	EmitVertex();

	EndPrimitive();
}