#pragma once
#include "Gui.h"
#include "Camera.h"
#include "Texture.h"
#include "Shader.h"

struct Particle
{
	glm::vec4 position;
	glm::vec4 direction;
};

class ParticleSystem {
public:
	ParticleSystem();
	~ParticleSystem();
	void update(GuiVals& guiVals);
	void render(std::shared_ptr<Camera> cam);
private:
	unsigned int m_numParts;
	unsigned int m_SSBO;
	unsigned int m_VAO;
	unsigned int billScale;
	double lastTime;
	Texture* billTex;
	glm::vec3 m_emmiterLocation;
	Shader* m_computeInitialise;
	Shader* m_computeUpdate;
	Shader* m_particleDrawer;

	void initialise();
};

