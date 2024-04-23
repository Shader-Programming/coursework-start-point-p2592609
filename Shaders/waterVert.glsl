#version 410 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aUV;

out vec2 UV;
out vec3 PosInWS;
out vec3 normal;
out mat3 TBN;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    PosInWS = aPos;
    gl_Position = projection * view * vec4(aPos, 1.f);

    vec3 T = (mat4(1.f) * vec4(vec3(1.0f, 0.f, 0.f), 0.0)).xyz;
	vec3 N = normal;
	vec3 B = normalize(cross(T, N));
  
    UV = aUV;
    normal = vec3(0.0, -1.0,0.0) ;  // for now plane is flat so all normals pointing up

}