#pragma once
#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_glfw.h"
#include "IMGUI/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/common.hpp>

struct GuiVals {
	glm::vec3 lightDir = glm::vec3(0.0,-1.0f,0.0f);
	glm::vec3 floorCol = glm::vec3(.1f , .1f, .1f);
	glm::vec3 lightCol = glm::vec3(1.f);
	bool showWireFrame = false;
	bool cdm = false;
	bool textureView = false;
	float scale = 1.f;
	float hmScale = 30.f;

};

class Gui {

public:

	Gui(GLFWwindow* window);
	~Gui();
	void newGuiFrame();
	void drawGui();
	GuiVals getVals() { return guiVals; }
	bool isActive;


private:
	GLFWwindow* m_window;
	GuiVals guiVals;

};
