#version 330 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec2 UV[];
in vec3 posInWS[];

out vec2 gUV;
out vec3 gNormal;
out vec3 gPosInWS;

vec3 getSurfaceNormal();

void main()
{

	for (int i = 0; i < 3; i++)
	{
		gl_Position = gl_in[i].gl_Position;
		gUV = UV[i];
		gNormal = getSurfaceNormal();
		gPosInWS = posInWS[i];
		EmitVertex();
	}
	EndPrimitive();
}

vec3 getSurfaceNormal()
{
	vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
	vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
	return normalize(cross(a, b));
}