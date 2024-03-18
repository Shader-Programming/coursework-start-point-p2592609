#version 330 core
out vec4 FragColor;

uniform sampler2D image;

in vec2 uv;
in float ageGS;

vec3  flameCol = vec3(.866, .345, .133);

void main()
{
	vec3 col = texture(image,uv).rgb;
	//float alpha = ageGS / 300;
	//float mixer = ageGS / 300;
	//if (col < 0.01f)
	//	discard;
	//flameCol = mix(flameCol, vec3(1.0), mixer);
	FragColor = vec4(col, 1);
}