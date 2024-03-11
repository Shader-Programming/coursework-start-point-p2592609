#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	m_particleDrawer = new Shader("..\\shaders\\particlesBillVert.glsl", "..\\shaders\\particlesBillFrag.glsl", "..\\shaders\\particlesBillGeo.glsl");
	m_computeInitialise = new Shader("..\\Shaders\\particleInit.glsl");
	m_computeUpdate = new Shader("..\\Shaders\\particleUpdate.glsl");
	initialise();
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::update(GuiVals& guiVals)
{
}

void ParticleSystem::render(std::shared_ptr<Camera> cam)
{
	m_particleDrawer->use();
	m_particleDrawer->setMat4("projection", cam->getProjectionMatrix());
	m_particleDrawer->setMat4("view", cam->getViewMatrix());
	m_particleDrawer->setMat4("model", glm::mat4(1.f));
	m_particleDrawer->setVec3("cameraPos", cam->getPosition());
	m_particleDrawer->setInt("billboard", 0);
	m_particleDrawer->setInt("scale", billScale);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, billTex->getID());
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_POINTS, 0, 5);
}

void ParticleSystem::initialise()
{
	//create buffers
	glGenVertexArrays(1, &m_VAO);
	//bind buffers
	glBindVertexArray(m_VAO);



	glGenBuffers(1, &m_SSBO);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_SSBO);
	glBufferData(GL_SHADER_STORAGE_BUFFER, m_numParts * sizeof(Particle), NULL, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_SSBO);

	m_computeInitialise->use();
	m_computeInitialise->setVec3("origin", m_emmiterLocation);
	m_computeInitialise->setFloat("seed", glfwGetTime());
	glDispatchCompute(m_numParts, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}
