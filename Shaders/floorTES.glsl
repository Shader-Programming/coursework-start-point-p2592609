#version 450

layout(triangles, equal_spacing, ccw) in;

out vec3 tePosInWS;
out vec2 teUV;
out vec3 teNorm;

in vec3 tcPosInWS[];
in vec2 tcUV[];

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform sampler2D heightMap;
uniform float hmScale;

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2);
vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2);

void main()
{
	tePosInWS = interpolate3D(tcPosInWS[0], tcPosInWS[1], tcPosInWS[2]);
	teUV = interpolate2D(tcUV[0], tcUV[1], tcUV[2]);
	float h = (texture(heightMap, teUV).r);
	//h = h*2.0 - 1.0;
	tePosInWS.y = h * hmScale;
	gl_Position = projection * view * model *vec4(tePosInWS, 1.0);

	float right = (textureOffset(heightMap, teUV, ivec2(5, 0)).r) * hmScale;
	float left = (textureOffset(heightMap, teUV, ivec2(-5, 0)).r) * hmScale;
	float up = (textureOffset(heightMap, teUV, ivec2(0, -5)).r) * hmScale;
	float down = (textureOffset(heightMap, teUV, ivec2(0, 5)).r) * hmScale;

	float lr = left - right;
	float du = up - down;
	teNorm = normalize(vec3(lr, 2.0, du));
}

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{ 
	return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2)
{
	return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
}