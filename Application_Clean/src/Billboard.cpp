#include "Billboard.h"

Billboard::Billboard()
{
	m_shader = new Shader("..\\shaders\\billboardVertex.glsl", "..\\shaders\\billboardFrag.glsl", "..\\shaders\\billboardGeo.glsl");
	stbi_set_flip_vertically_on_load(true);
	m_billboardTexture = new Texture("..\\Resources\\tree.jpg");
	stbi_set_flip_vertically_on_load(false);
	makeVAO();
}

void Billboard::render(std::shared_ptr<Camera> camera, int scale)
{
	m_shader->use();
	m_shader->setMat4("projection", camera->getProjectionMatrix());
	m_shader->setMat4("view", camera->getViewMatrix());
	m_shader->setMat4("model", m_model);
	m_shader->setVec3("cameraPos", camera->getPosition());
	m_shader->setInt("billboard", 0);
	m_shader->setInt("scale", scale);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_billboardTexture->getID());
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_POINTS, 0, 5);
}

void Billboard::makeVAO()
{
	//create buffers
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	//bind buffers
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	//transfer data to GPU
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sizeof(positions), positions, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}
