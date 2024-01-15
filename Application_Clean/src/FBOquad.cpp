#include "FBOquad.h"


FBOquad::FBOquad()
{
	m_colShader = std::make_shared<Shader>("..\\Shaders\\PostProcessingVertexShader.glsl", "..\\Shaders\\PostProcessingFragmentShader.glsl");
	m_depthShader = std::make_shared<Shader>("..\\Shaders\\PostProcessingVertexShader.glsl", "..\\Shaders\\DepthFragmentShader.glsl");
	makeVAO();
}

void FBOquad::drawColAttachment(unsigned int texID)
{
	glBindVertexArray(VAO);
	m_colShader->use();
	m_colShader->setInt("defaultTexture", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID);
	glDrawElements(GL_TRIANGLES, getIndicesCount(), GL_UNSIGNED_INT, 0);
}

void FBOquad::drawDepthAttachment(unsigned int texID)
{
	glBindVertexArray(VAO);
	m_depthShader->use();
	m_depthShader->setInt("image", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID);
	glDrawElements(GL_TRIANGLES, getIndicesCount(), GL_UNSIGNED_INT, 0);
}

void FBOquad::makeVAO()
{
	//create buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	//bind buffers
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);
	//transfer data to GPU
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

}
