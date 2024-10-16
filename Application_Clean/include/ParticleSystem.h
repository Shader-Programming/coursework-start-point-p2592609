#pragma once

#include "Camera.h"
#include "Texture.h"
#include "Shader.h"
#include "Gui.h"

struct Particle
{
	glm::vec4 position;
	glm::vec4 direction;
};

class ParticleSystem {
public:
	ParticleSystem(glm::vec3 location, unsigned int numParts, std::shared_ptr<Texture> texture, unsigned int scale);
	~ParticleSystem();
	void update(GuiVals& guiVals);
	void render(std::shared_ptr<Camera> cam);
private:
	unsigned int m_numParts;
	unsigned int m_SSBO;
	unsigned int m_VAO;
	unsigned int billScale;
	double lastTime;
	std::shared_ptr<Texture> billTex;
	glm::vec3 m_emmiterLocation;
	Shader* m_computeInitialise;
	Shader* m_computeUpdate;
	Shader* m_particleDrawer;

	void initialise();
};

