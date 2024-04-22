#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "glm/common.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <memory>
#include "Shader.h"

class WaterQuad
{
public:
	WaterQuad(int widthIn, int heightIn, int stepSizeIn);
	WaterQuad();
	void init();
	~WaterQuad() {};

	int getSize();
	unsigned int getVAO() { return m_VAO; }


private:
	std::vector<float> m_vertices;
	unsigned int m_VAO;
	int width;
	int height;
	int stepSize;
	void makeVertices();
	void makeVertex(int x, int z);
	std::vector<float> getVertices();
	void makeVAO();


};