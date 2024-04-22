#version 330 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec2 UV[];
in vec3 PosInWS[];


out vec2 gUV;
out vec3 gNormal;
out vec3 gPosInWS;
//out vec3 cdmNorm;



void main()
{

	for (int i = 0; i < 3; i++)
	{
		gl_Position = gl_in[i].gl_Position;
		gUV = UV[i];
		gNormal = vec3(0.0, 1.0, 0.0);
		//cdmNorm = teNorm[i];
		gPosInWS = PosInWS[i];
		EmitVertex();
	}
	EndPrimitive();
}

