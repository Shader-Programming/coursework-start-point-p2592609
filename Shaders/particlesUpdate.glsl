#version 430 core


struct Particle {
    vec4 position;
    vec4 direction;
};

layout(local_size_x = 1, local_size_y = 1) in;

layout(std430, binding = 0) buffer particles
{
    Particle part[];
};

uniform vec3 origin;
uniform float seed;
uniform float DT;
uniform float acceleration;
uniform float speed;
float PI = 3.14159265;

vec3 randomUnitVector(float seed);
float randInRange(float seed);
vec3 updateVelocity(vec3 current);
vec3 updatePosition(vec3 currentPos, vec3 currentVel);

void main()
{
    unsigned int partID = gl_GlobalInvocationID.x;
    part[partID].position.w -= 1;
    if (part[partID].position.w < 0)
    {

        part[partID].position.xyz = origin;
        part[partID].direction.xyz = randomUnitVector(seed * gl_GlobalInvocationID.x);
        part[partID].position.w = randInRange(seed * gl_GlobalInvocationID.x) * 1000;
    }
    else
    {
        part[partID].direction.xyz = updateVelocity(part[partID].direction.xyz);
        part[partID].position.xyz = updatePosition(part[partID].position.xyz, part[partID].direction.xyz);
    }

}

// generate a random vector on unit sphere
vec3 randomUnitVector(float seed) {

    float theta = randInRange(seed) * 2.0 * PI; // Angle around the y-axis
    float phi = acos(2.0 * randInRange(seed + 1.0) - 1.0); // Angle from the positive y-axis 

    // Convert spherical coordinates to Cartesian coordinates
    float x = sin(phi) * cos(theta);
    float y = cos(phi);
    float z = sin(phi) * sin(theta);

    return vec3(x, y, z);
}

float randInRange(float seed) {
    // Generate a random number between 0 and 1
    return fract(sin(seed) * 43758.5453123);

}

vec3 updateVelocity(vec3 current)
{
    return current + acceleration * DT;
}

vec3 updatePosition(vec3 currentPos, vec3 currentVel)
{
    vec3 displacement = currentVel * DT + 0.5 * acceleration * DT * DT;
    return currentPos + displacement * speed;
}