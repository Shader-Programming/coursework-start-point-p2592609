#pragma once

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "glm/common.hpp"

#include "Mesh.h"
#include <memory>

class Model {
public:
	Model() {};
	Model(std::vector<Mesh> meshes, std::vector<Texture*> textures);
	inline std::vector<Texture*>& getTextures() { return m_textures; }
	inline std::vector<Mesh>& getModel() { return m_meshes; }
	void renderModel(std::shared_ptr<Shader>& shader);

	void rotate(float angle, glm::vec3 axis);
	void scale(float scaleFactor, glm::vec3 axis);
	void translate(glm::vec3 translation);

private:


	void createBuffers();
	glm::mat4 m_model = glm::mat4(1.0f);
	std::vector<Mesh> m_meshes;
	std::vector<Texture*> m_textures;






};

