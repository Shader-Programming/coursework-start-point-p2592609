#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aUV;

out vec2 UV;
out vec3 PosInWS;

uniform mat4 view;
uniform mat4 projection;
//uniform vec4 plane;

void main()
{
    PosInWS = aPos;
    //gl_ClipDistance[0] = dot(vec4(PosInWS, 1.0), plane);
    gl_Position = projection * view * vec4(aPos, 1.f);
  
    UV = aUV;
    //normal = vec3(0.0,1.0,0.0) ;  // for now plane is flat so all normals pointing up

}