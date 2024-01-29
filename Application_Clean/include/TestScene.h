#pragma once
# include "Scene.h"
# include "Shader.h"
#include "Gui.h"
#include "Texture.h"
#include "Terrain.h"
#include "SkyBox.h"
#include "ModelLoader.h"
#include "Billboard.h"


class TestScene : public Scene {

public:
	TestScene(GLFWwindow* window, std::shared_ptr<InputHandler> H);
	~TestScene();
	void update(float dt) override;

private:
	void processInput(float dt);
	void render();

	std::shared_ptr<Gui> m_gui;
	std::shared_ptr<Shader> m_floorShader;
	std::shared_ptr<Terrain> m_terrain;
	std::shared_ptr<SkyBox> m_skyBox;
	glm::mat4 m_view, m_projection;

	GuiVals guiVals;

	//Models
	std::unique_ptr<ModelLoader> m_modelLoader;
	std::shared_ptr<Model> m_vampire;
	std::shared_ptr<Shader> m_modelShader;

	std::shared_ptr<Billboard> m_billboard;
	

};