#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(glm::vec3 location, unsigned int numParts, std::shared_ptr<Texture> texture, unsigned int scale)
{
	m_particleDrawer = new Shader("..\\shaders\\particlesBillVert.glsl", "..\\shaders\\particlesBillFrag.glsl", "..\\shaders\\particlesBillGeo.glsl");
	m_computeInitialise = new Shader("..\\Shaders\\particleInit.glsl");
	m_computeUpdate = new Shader("..\\Shaders\\particlesUpdate.glsl");
	m_emmiterLocation = location; 
	m_numParts = numParts;
	billTex = texture;
	billScale = scale;
	initialise();
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::update(GuiVals& guiVals)
{

	float currentTime = glfwGetTime();
	float deltaTime = currentTime - lastTime;
	m_computeUpdate->use();
	m_computeUpdate->setVec3("origin", m_emmiterLocation);
	m_computeUpdate->setFloat("seed", glfwGetTime());
	m_computeUpdate->setFloat("DT", deltaTime);
	m_computeUpdate->setFloat("acceleration", guiVals.acceleration);
	m_computeUpdate->setFloat("speed",guiVals.speed);

	glDispatchCompute(m_numParts, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
	lastTime = currentTime;
}

void ParticleSystem::render(std::shared_ptr<Camera> cam)
{
	m_particleDrawer->use();
	m_particleDrawer->setMat4("projection", cam->getProjectionMatrix());
	m_particleDrawer->setMat4("view", cam->getViewMatrix());
	m_particleDrawer->setMat4("model", glm::mat4(1.f));
	m_particleDrawer->setVec3("cameraPos", cam->getPosition());
	m_particleDrawer->setInt("image", 0);
	m_particleDrawer->setInt("scale", billScale);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, billTex->getID());
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_POINTS, 0, m_numParts);
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
