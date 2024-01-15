#include "Lights/PointLight.h"

PointLight::PointLight(glm::vec3 colour, glm::vec3 position, glm::vec3 constants) : Light(colour), m_position(position),
m_constants(constants)
{
	
}

void PointLight::setLightUniforms(std::shared_ptr<Shader> shader, int i)
{
	shader->use();
	shader->setVec3("pLights[" + std::to_string(i) + "].plightPosition", m_position);
	shader->setVec3("pLights[" + std::to_string(i) + "].plightColour", m_colour);
	shader->setVec3("pLights[" + std::to_string(i) + "].pAttentuation", m_constants);
}
