#include "SkyBox.h"

SkyBox::SkyBox()
{
    skyBoxShader = new Shader("..\\Shaders\\SBvertex.glsl", "..\\Shaders\\SBfrag.glsl");
    createSkyBox();
}

void SkyBox::renderSkyBox(glm::mat4 projectionView)
{
    skyBoxShader->use();
    skyBoxShader->setMat4("projectionView", projectionView);
    glDepthMask(GL_FALSE);
    glBindVertexArray(skyBoxVAO);
    skyBoxShader->setInt("skybox", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyBoxObj);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glDepthMask(GL_TRUE);
}

void SkyBox::createSkyBox()
{
    loadCubeMapTextures();
    createVAO();
}

void SkyBox::loadCubeMapTextures()
{
    faces.push_back("..\\Resources\\SkyBox_Textures\\right.png");
    faces.push_back("..\\Resources\\SkyBox_Textures\\left.png");
    faces.push_back("..\\Resources\\SkyBox_Textures\\top2.png");
    faces.push_back("..\\Resources\\SkyBox_Textures\\bottom.png");
    faces.push_back("..\\Resources\\SkyBox_Textures\\back.png");
    faces.push_back("..\\Resources\\SkyBox_Textures\\front.png");
    skyBoxObj = loadCubeMap(faces);
}

unsigned int SkyBox::loadCubeMap(std::vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            std::cout << "Loaded texture at path: " << faces[i] << " width " << width << " id " << textureID << std::endl;
            stbi_image_free(data);
        }
        else {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

void SkyBox::createVAO()
{
    //create buffers
    glGenVertexArrays(1, &skyBoxVAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    //bind buffers
    glBindVertexArray(skyBoxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), skyboxIndices, GL_STATIC_DRAW);
    //transfer data to GPU
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}
