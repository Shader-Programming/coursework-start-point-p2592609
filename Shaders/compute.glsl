#version 430
layout(local_size_x = 32, local_size_y = 16) in;
layout(binding = 0, rgba32f) uniform image2D outputImg;

void main() {
	vec4 pixel = vec4(1.0, 0.0, 0.0, 1.0);
	ivec2 pixel_coords = ivec2(gl_GlobalInvocationID.xy);
	imageStore(outputImg, pixel_coords, pixel);
}