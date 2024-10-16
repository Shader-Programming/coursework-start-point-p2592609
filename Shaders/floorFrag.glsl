#version 410 core

///////////////////////// INS OUTS
out vec4 FragColor;

in vec2 gUV ;
in vec3 gNormal ;
in vec3 gPosInWS ;
in vec3 cdmNorm;


///////////////////////// UNIFORMS
uniform vec3 lightDirection ;
uniform vec3 floorCol ;
uniform vec3 viewPos ;
uniform bool cdm;
uniform float hmScale;
uniform sampler2D grass;
uniform sampler2D rock;

///////////////////////// FUNCTIONS
vec3 getDirectionalLight() ;

///////////////////////// VARS
// constants for now, could be added to imGui?
float ambientFactor = 0.3 ;
float shine = 16.0f ;
float specularStrength = 0.3f ;
vec3 lightColour = vec3(1.0f) ;
vec3 viewDir ;
vec3 n ;
vec3 lightDir ;

///////////////////////// MAIN

void main()
{   
    if (cdm)
    {
        n = normalize(cdmNorm);
    }
    else if (!cdm)
    {
        n = normalize(gNormal);
    }
    viewDir = normalize(viewPos - gPosInWS);
    lightDir = -normalize(lightDirection) ;
    lightDir.y = max(lightDir.y, 0.0) ; // Gui slider goes from [-1,1], direction light can only go from [0,1]

    float mid = hmScale * 0.5;

    vec3 col1 = texture(grass, gUV).rgb;
    vec3 col2 = texture(rock, gUV).rgb;
    vec3 col = mix(col1, col2, smoothstep(0.0, mid + mid * 0.5, gPosInWS.y));
   
    vec3 result = getDirectionalLight() ;
    result += col;
    FragColor = vec4(result, 1.0f);   
}


///////////////////////// DIRECTIONAL LIGHT

vec3 getDirectionalLight() { 
   

   // ambient
  vec3 ambient = floorCol * lightColour * ambientFactor;

  //diffuse 
  float diffuseFactor = dot(n,lightDir) ;
  diffuseFactor = max(diffuseFactor, 0.0f) ;
  vec3 diffuse = floorCol * lightColour * diffuseFactor;


  // Blinn Phong specular
  vec3 H = normalize(lightDir + viewDir ) ;  
  float specLevel = dot(n, H) ;   
  specLevel = max(specLevel, 0.0) ; 
  specLevel = pow(specLevel, shine) ; 
  vec3 specular = lightColour*specLevel* specularStrength;

  return ambient + specular + diffuse;

}