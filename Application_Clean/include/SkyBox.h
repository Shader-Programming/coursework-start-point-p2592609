#pragma once
#include "Shader.h"
#include <vector>
#include "stb_image.h"
#include <iostream>


class SkyBox
{
public:
    SkyBox();
    void renderSkyBox(glm::mat4 projectionView);
private:
	Shader* skyBoxShader;
	void createSkyBox(); 
	void loadCubeMapTextures();
	unsigned int loadCubeMap(std::vector<std::string> faces);
	void createVAO();

	std::vector<std::string> faces;
	unsigned int skyBoxObj;
    unsigned int skyBoxVAO, VBO, EBO;

    const float skyboxVertices[24] = {
        // Positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f
    };

    const unsigned int skyboxIndices[36] = {
    0, 1, 2, 2, 3, 0,
    4, 5, 6, 6, 7, 4,
    7, 3, 0, 0, 4, 7,
    1, 5, 6, 6, 2, 1,
    4, 5, 1, 1, 0, 4,
    7, 6, 2, 2, 3, 7
    };

};