#version 330 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec2 teUV[];
in vec3 tePosInWS[];
in vec3 teNorm[];


out vec2 gUV;
out vec3 gNormal;
out vec3 gPosInWS;
out vec3 cdmNorm;

uniform vec4 plane;

vec3 getSurfaceNormal();

void main()
{
	
	for (int i = 0; i < 3; i++)
	{
		gl_ClipDistance[0] = dot(vec4(tePosInWS[i], 1.0), plane);
		gl_Position = gl_in[i].gl_Position;
		gUV = teUV[i];
		gNormal = getSurfaceNormal();
		cdmNorm = teNorm[i];
		gPosInWS = tePosInWS[i];
		EmitVertex();
	}
	EndPrimitive();
}

vec3 getSurfaceNormal()
{
	vec3 a = tePosInWS[1] - tePosInWS[0];
	vec3 b = tePosInWS[2] - tePosInWS[0];
	return normalize(cross(a, b));
}