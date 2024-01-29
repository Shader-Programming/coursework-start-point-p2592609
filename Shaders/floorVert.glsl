#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

out vec2 UV;
out vec3 posInWS ;


void main()
{  
    posInWS = aPos;
    gl_Position = aPos;
    UV = aUV ;
    //normal = vec3(0.0,1.0,0.0) ;  // for now plane is flat so all normals pointing up
    
}