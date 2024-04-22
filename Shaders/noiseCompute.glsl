#version 430
layout(local_size_x = 32, local_size_y = 16) in;
layout(binding = 0, rgba32f) uniform image2D outputImg;

uniform float frequency;
uniform float amplitude;
uniform float persistence;
uniform float lacunarity;
uniform int octaves;
/*uniform*/ int noiseFBM = 2;


float remap(float currValue, float  inMin, float inMax, float outMin, float outMax);
vec2 hash2(vec2 p);
float noise(in vec2 p);
float FBM(vec2 position, int octaves);
float RFBM(vec2 position, int octaves);
float TFBM(vec2 position, int octaves);

void main() {

	ivec2 pixel_coords = ivec2(gl_GlobalInvocationID.xy);
	vec2 pc = vec2(float(pixel_coords.x) / 512.f, float(pixel_coords.y) / 512.f);
	float p = FBM(pc, octaves);
	/*if (noiseFBM == 0)
	{
		p += FBM(pc, octaves);
	}
	else if (noiseFBM == 1)
	{
		p = RFBM(pc, octaves);
	}
	else if (noiseFBM == 2)
	{
		p = TFBM(pc, octaves);
	}*/

	//p = noise(pc * 10.0) * 1.5;
	p = remap(p, -1, 1, 0, 1);

	vec4 pixel = vec4(vec3(p), 1.0);
	imageStore(outputImg, pixel_coords, pixel);


}

float remap(float currValue, float  inMin, float inMax, float outMin, float outMax) {

	float t = (currValue - inMin) / (inMax - inMin);
	return mix(outMin, outMax, t);
}


// The MIT License
// Copyright © 2013 Inigo Quilez
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
// https://www.youtube.com/c/InigoQuilez
// https://iquilezles.org/
//
// https://www.shadertoy.com/view/Xsl3Dl



vec2 hash2(vec2 p)
{
	p = vec2(dot(p, vec2(127.1, 311.7)),
		dot(p, vec2(269.5, 183.3)));

	return -1.0 + 2.0 * fract(sin(p) * 43758.5453123);
}

float noise(in vec2 p)
{
	vec2 i = floor(p);
	vec2 f = fract(p);

	vec2 u = f * f * (3.0 - 2.0 * f);

	return mix(mix(dot(hash2(i + vec2(0.0, 0.0)), f - vec2(0.0, 0.0)),
		dot(hash2(i + vec2(1.0, 0.0)), f - vec2(1.0, 0.0)), u.x),
		mix(dot(hash2(i + vec2(0.0, 1.0)), f - vec2(0.0, 1.0)),
			dot(hash2(i + vec2(1.0, 1.0)), f - vec2(1.0, 1.0)), u.x), u.y);
}

float FBM(vec2 position, int octaves) {
	float f = frequency;
	float a = amplitude;
	float total = 0.0f;
	float totalAmplitude = 0.0f;
	for (int i = 0; i < octaves; i++)
	{
		total += noise(position * f) * a;
		f *= lacunarity;
		a *= persistence;
		totalAmplitude += a;
	}
	return (total / totalAmplitude);
}

float RFBM(vec2 position, int octaves) {
	float f = frequency;
	float a = amplitude;
	float total = 0.0f;
	float totalAmplitude = 0.0f;
	for (int i = 0; i < octaves; i++)
	{
		total += noise(position * f) * a;
		f *= lacunarity;
		a *= persistence;
		totalAmplitude += a;
	}
	float noiseVal = noise(position * f);
	noiseVal = abs(noiseVal);
	noiseVal = 1.0 - noiseVal;
	total += noiseVal * a;
	total =(total / totalAmplitude);
	return total * total;
}

float TFBM(vec2 position, int octaves) {
	float f = frequency;
	float a = amplitude;
	float total = 0.0f;
	float totalAmplitude = 0.0f;
	for (int i = 0; i < octaves; i++)
	{
		total += noise(position * f) * a;
		f *= lacunarity;
		a *= persistence;
		totalAmplitude += a;
	}
	float noiseVal = noise(position * f);
	noiseVal = abs(noiseVal);
	total += noiseVal * a;
	total = (total / totalAmplitude);
	return total * total;
}