#version 410 core

///////////////////////// INS OUTS
out vec4 FragColor;

in vec2 UV;
//in vec3 gNormal;
in vec3 PosInWS;

uniform sampler2D refraction;
uniform sampler2D reflection;

uniform float screenW;
uniform float screenH;

void main()
{
	vec4 blue = vec4(0.1f, 0.4f, 1.0f, 1.0f);
	vec2 ndcXY = gl_FragCoord.xy;
	vec2 refractTex = vec2((ndcXY.x) / screenW, (ndcXY.y) / screenH);
	vec2 reflectTex = vec2((ndcXY.x) / screenW, (-ndcXY.y) / screenH);
	vec4 refract = texture(refraction, refractTex);
	vec4 reflect = texture(reflection, reflectTex);
	//float fresnel = pow(dot(UP, viewDir), 5.0);
	FragColor = mix(reflect, refract, 0.5);
	FragColor = mix(FragColor, blue, 0.3);
	//FragColor = vec4(0.1f, 45.0f, 1.0f, 1.0f);
}