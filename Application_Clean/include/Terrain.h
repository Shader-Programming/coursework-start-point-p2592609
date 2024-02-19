#pragma once


#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Shader.h"
#include "Texture.h"

class Terrain
{
public:
	Terrain(int widthIn, int heightIn, int stepSizeIn);
	Terrain();
	void init();
	void makeVAO();
	unsigned int getVAO() { return m_VAO; }
	int getSize();
	void setHeightMap(std::shared_ptr<Shader> shader);
	unsigned int getHeightMap() { return m_heightMapID->getID(); }

private:
	std::vector<float> m_vertices;
	unsigned int m_VAO;
	int width;
	int height;
	int stepSize;
	void makeVertices();
	void makeVertex(int x, int z);
	std::vector<float> getVertices();
	Texture* m_heightMapID;
	Texture* m_grass;
	Texture* m_rock;
};