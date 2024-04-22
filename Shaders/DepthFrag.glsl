#version 330 core

float LinearizeDepth(float depth) ;

out vec4 FragColor;
in vec2 uv;

uniform sampler2D image ;

const float near_plane = 1.0f;
const float far_plane = 100;

void main()
{ 
    float depth = texture(image, uv).r ;

    FragColor = vec4(vec3(LinearizeDepth(depth) ), 1.0);
    //FragColor = vec4(1.f, 0.f, 1.f, 1.f);
}

   // required when using a perspective projection matrix
float LinearizeDepth(float depth)
{
       float z = depth * 2.0 - 1.0; // Back to NDC 
       float viewSpacePosition =  (2.0 * near_plane * far_plane) / (far_plane + near_plane - z * (far_plane - near_plane));	

       return viewSpacePosition / far_plane;  // divide by far to visualise
}