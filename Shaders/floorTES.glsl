#version 450

layout(triangles, equal_spacing, ccw) in;

out vec3 tePosInWS;
out vec2 teUV;

in vec3 tcPosInWS[];
in vec2 tcUV[];

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2);
vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2);

void main()
{
	tePosInWS = interpolate3D(tcPosInWS[0], tcPosInWS[1], tcPosInWS[2]);
	teUV = interpolate2D(tcUV[0], tcUV[1], tcUV[2]);

	gl_Position = projection * view * model *(tePosInWS, 1.0);
}

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{ 
	return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2);
{
	return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}