#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "glm/common.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <memory>
#include "Shader.h"

class FBOquad
{
public:
	FBOquad();
	~FBOquad() {};

	void drawColAttachment(unsigned int texID);
	void drawDepthAttachment(unsigned int texID);

	unsigned int getIndicesCount() { return sizeof(quadIndices); }
	unsigned int getVAO() { return VAO; }

private:
	unsigned int VAO, EBO, VBO;

	std::shared_ptr<Shader> m_colShader;
	std::shared_ptr<Shader> m_depthShader;

	void makeVAO();

	float quadVertices[20] = {
		// positions        // texture Coords
		 -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		  1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,


		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,

	};

	unsigned int quadIndices[6] = {
			3,2,1,
			3,1,0
	};

};