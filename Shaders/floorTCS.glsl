#version 450 core
layout(vertices = 3) out;

in vec2 UV[];
in vec3 posInWS[];

out vec2 tcUV[];
out vec3 tcPosInWS[];

void main()
{
	float tessLevel = 1.f;
	if (gl_InvocationID == 0)
	{
		gl_TessLevelOuter[0] = tessLevel;
		gl_TessLevelOuter[1] = tessLevel;
		gl_TessLevelOuter[2] = tessLevel;
		gl_TessLevelInner[0] = tessLevel;
	}
	tcUV[gl_InvocationID] = UV[gl_InvocationID];
	tcPosInWS[gl_InvocationID] = PosInWS[gl_InvocationID];
}