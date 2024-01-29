#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "FPSCamera.h"
#include "Texture.h"
#include <memory>

class Billboard
{
public:
	Billboard();
	unsigned int getVAO() { return m_VAO; }
	Shader* m_shader;
	void render(std::shared_ptr<Camera> camera, int scale);

	void scale(int scaleFactor);
	void translate(glm::vec3 translation);

private:
	void makeVAO();
	unsigned int m_VAO, m_VBO;
	Texture* m_billboardTexture;
	glm::mat4 m_model;
	float positions[15] = {
		-2.f, 0.f, 0.f,
		2.f, 0.f, 4.f,
		0.f, 0.f, 2.f,
		2.f, 0.f, 0.f,
		-2.f, 0.f, 4.f,
	};
};