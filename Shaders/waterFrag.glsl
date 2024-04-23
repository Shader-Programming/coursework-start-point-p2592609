#version 410 core

///////////////////////// INS OUTS
out vec4 FragColor;

in vec2 UV;
in vec3 normal;
in vec3 PosInWS;
in mat3 TBN;

uniform sampler2D refraction;
uniform sampler2D reflection;

uniform float screenW;
uniform float screenH;
uniform vec3 UP;
uniform vec3 viewPos;
uniform sampler2D dudvMap;
uniform float time;
uniform sampler2D normalMap;
uniform float rate;


void main()
{

	vec3 n = normalize(normal);
	vec4 blue = vec4(0.54f, 0.8f, 0.60f, 1.0f);

	vec2 D = (texture(dudvMap, vec2(UV.x + time, UV.y)).rg * 2.0 - 1.0) * rate;
	vec2 D2 = (texture(dudvMap, vec2(-UV.x + time, UV.y+ time)).rg * 2.0 - 1.0) * rate;
	vec2 totalD = (D+D2);
	
	vec2 ndcXY = gl_FragCoord.xy;
	vec2 refractTex = vec2((ndcXY.x) / screenW, (ndcXY.y) / screenH);
	vec2 reflectTex = vec2((ndcXY.x) / screenW, (-ndcXY.y) / screenH);
	
	reflectTex = reflectTex + totalD;
	reflectTex.x = clamp(reflectTex.x, 0, 1);
	reflectTex.y = clamp(reflectTex.y, -1, 0);

	refractTex = refractTex + totalD;
	refractTex = clamp(refractTex, 0, 1);

	vec4 refract = texture(refraction, refractTex);
	vec4 reflect = texture(reflection, reflectTex);

	n = texture(normalMap, UV).rgb;
	n = n * 2.0 - 1.0;
	n = normalize(TBN * n);

	vec3 viewDir = normalize(viewPos - PosInWS);
	float fresnel = pow(dot(UP, viewDir), 5.0);
	FragColor = mix(reflect, refract, 0.5);
	FragColor = mix(FragColor, blue, 0.3);
	//FragColor = vec4(0.1f, 45.0f, 1.0f, 1.0f);
}