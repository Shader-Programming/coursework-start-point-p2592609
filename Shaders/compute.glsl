#version 430
layout(local_size_x = 32, local_size_y = 16) in;
layout(binding = 0,rgba32f) uniform image2D outputImg;

uniform sampler2D inputImg;
uniform vec3 col;

void main() {
	vec4 pixel = vec4(1.0, 0.0, 0.0, 1.0);
	ivec2 pixel_coords = ivec2(gl_GlobalInvocationID.xy);

	/*float texelSize = 1.0 / 512.0;
	ivec2 pixel_coords = ivec2(gl_GlobalInvocationID.xy);
	vec2 pixel_coordsUV = pixel_coords * vec2(texelSize, texelSize);

	vec4 pixel = texture(inputImg, pixel_coordsUV);*/

	imageStore(outputImg, pixel_coords, pixel);


}