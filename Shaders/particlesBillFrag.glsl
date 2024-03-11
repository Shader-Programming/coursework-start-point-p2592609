#version 330 core
out vec4 FragColor;

uniform sampler2D iamge;

in vec2 uv;
in float ageGS;

vec3  flameCol = vec3(.866, .345, .133);

void main()
{
	float col = texture(image.uv).r;
	float alpha = ageGS / 300;
	float mixer = ageGS / 300;
	if (col < 0.01f)
		discard;
	flameCol = mix(flameCol, vec3(1.0), mixer);
	FragColor = vec4(flameCol, alpha);
}