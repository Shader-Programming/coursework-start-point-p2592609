#version 330 core

out vec4 FragColor;

in vec3 normal;
in vec3 posInWS;
in vec2 uv;
in mat3 TBN;

uniform vec3 viewPos;

//Material Props
uniform float shine;
uniform sampler2D diffuseTexture;
uniform sampler2D specTexture;
uniform sampler2D normalTexture;


//Directional Light
uniform vec3 lightColour;
uniform vec3 lightDirection;
uniform float ambientFactor;

vec3 n = normalize(normal);
vec3 viewDir = normalize(viewPos - posInWS);

vec3 getDirectionalLight();

void main()
{
	vec3 n = normalize(normal);
	vec3 viewDir = normalize(viewPos - posInWS);

	vec3 result = getDirectionalLight();

	FragColor = vec4(result, 1.0); //RGBA

}

vec3 getDirectionalLight()
{

	n = texture(normalTexture, uv).rgb;
	n = n * 2.0 - 1.0;
	n = normalize(TBN * n);

	vec3 objCol = texture(diffuseTexture, uv).rgb;
	float specStrength = texture(specTexture, uv).r;

	vec3 ambient = objCol * lightColour * ambientFactor;

	float diffuseFactor = dot(n, -lightDirection);
	diffuseFactor = max(diffuseFactor, 0.0f);
	vec3 diffuse = objCol * lightColour * diffuseFactor;

	vec3 H = normalize(-lightDirection + viewDir);
	float specLevel = dot(n, H);
	specLevel = max(specLevel, 0.0);
	specLevel = pow(specLevel, shine);
	vec3 specular = lightColour * specLevel * specStrength;

	return ambient + diffuse + specular;
}