#pragma once

#include "PointLight.h"
#include "Shader.h"
#include <memory>

class SpotLight : public PointLight
{
public:
	SpotLight(glm::vec3 colour, glm::vec3 position, glm::vec3 constants, glm::vec3 dir, glm::vec2 radii);
	~SpotLight() {};

	void setLightUniforms(std::shared_ptr<Shader> shader);

	void setDirection(glm::vec3& dir) { m_direction = dir; }
	void setPosition(glm::vec2& r) { m_radii = r; }

	glm::vec2& getRadii() { return m_radii; }

private:
	glm::vec3 m_direction;
	glm::vec2 m_radii;
};