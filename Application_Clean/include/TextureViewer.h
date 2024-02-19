#pragma once
#include <memory>
#include "Shader.h"

class TextureViewer {
	
public:
	TextureViewer();
	~TextureViewer() {};
	void drawColourTexture(unsigned int texID);

	unsigned int getIndicesCount() { return sizeof(quadIndices); }
	unsigned int getVAO() { return VAO; }

private:
	unsigned int VAO, VBO, EBO;
	void createQuadVAO();

	std::unique_ptr<Shader> m_colShader;

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