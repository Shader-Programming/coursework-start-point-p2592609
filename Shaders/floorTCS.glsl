#version 450 core
layout(vertices = 3) out;

in vec2 UV[];
in vec3 PosInWS[];

out vec2 tcUV[];
out vec3 tcPosInWS[];

uniform float tessLevel;
uniform vec3 viewPos;

float GetTessLevel(float Distance0, float Distance1);

void main()
{

	float camToVertex0 = distance(viewPos, PosInWS[0]);
	float camToVertex1 = distance(viewPos, PosInWS[1]);
	float camToVertex2 = distance(viewPos, PosInWS[2]);

	if (gl_InvocationID == 0)
	{
		gl_TessLevelOuter[0] = GetTessLevel(camToVertex1, camToVertex2);
		gl_TessLevelOuter[1] = GetTessLevel(camToVertex2, camToVertex0);;
		gl_TessLevelOuter[2] = GetTessLevel(camToVertex0, camToVertex1);;
		gl_TessLevelInner[0] = gl_TessLevelOuter[2];
	}
	tcUV[gl_InvocationID] = UV[gl_InvocationID];
	tcPosInWS[gl_InvocationID] = PosInWS[gl_InvocationID];
}

float GetTessLevel(float Distance0, float Distance1)
{
	return 12.f;
	float AvgDistance = (Distance0 + Distance1) / 2.0;
	if (AvgDistance <= 20)
	{
		return 10.f;
	}
	else if (AvgDistance <= 40 )
	{
		return 5.f;
	}
	else if (AvgDistance <= 60)
	{
		return 3.f;
	}
	else
	{
		return 1.f;
	}
}