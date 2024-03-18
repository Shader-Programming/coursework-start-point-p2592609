#include "..\include\TestScene.h"

TestScene::TestScene(GLFWwindow* window, std::shared_ptr<InputHandler> H): Scene(window, H){
		// Shaders
		m_floorShader = std::make_shared<Shader>("..\\shaders\\floorVert.glsl", "..\\shaders\\floorFrag.glsl", "..\\shaders\\floorGeo.glsl", "..\\shaders\\floorTCS.glsl", "..\\shaders\\floorTES.glsl");
		// Camera & Input
		m_camera = std::make_shared<FirstPersonCamera>(glm::vec3(0,20,0));   
		m_camera->attachHandler(window, H);
		//imGui
		m_gui = std::make_shared<Gui>(m_window);

		//Terrain/ Plane
		m_terrain = std::make_shared<Terrain>();

		m_skyBox = std::make_shared<SkyBox>();

		m_modelLoader = std::make_unique<ModelLoader>();
		m_vampire = m_modelLoader->getModel("..\\Resources\\Models\\Vampire\\vampire.obj");

		m_modelShader = std::make_shared<Shader>("..\\shaders\\modelVertex.glsl", "..\\shaders\\modelFrag.glsl");

		m_billboard = std::make_shared<Billboard>();

		m_textureViewer = std::make_shared<TextureViewer>();

		m_emptyTexture = std::make_shared<Texture>(512, 512, 4);

		m_textureCompute = std::make_shared<Shader>("..\\Shaders\\compute.glsl");

		m_noiseCompute = std::make_shared<Shader>("..\\Shaders\\noiseCompute.glsl");

		m_terrain->setHeightMap(m_emptyTexture);

		m_particleSystem = std::make_shared<ParticleSystem>(glm::vec3(0.f, 10.f, 0.f), 5, m_emptyTexture, 3);
}


TestScene::~TestScene()
{
	
	
}

void TestScene::update(float dt)
{	
	processInput(dt);
	render();		
	m_vampire->rotate(dt, glm::vec3(0.0f, 1.0f, 0.0f));
	m_gui->newGuiFrame();
	m_gui->drawGui();
}


void TestScene::processInput(float dt)
{
	
	if (m_handler->isKeyPressed(GLFW_KEY_ESCAPE)) { glfwSetWindowShouldClose(m_window, GLFW_TRUE); }  // ESC to close
	if (m_handler->isKeyPressed(GLFW_KEY_TAB)) {  // TAB To use IMGui  
		m_gui->isActive = !m_gui->isActive; // gui active if tab pressed
		m_handler->gui = !m_handler->gui;
	}
	else {
		m_camera->update(dt); // only update if GUI not active
	}
	guiVals = m_gui->getVals(); // get the gui values
}


void TestScene::render()
{
	if (guiVals.showWireFrame) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else                       glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	
	if (!guiVals.textureView)
	{
		m_skyBox->renderSkyBox(m_camera->getProjectionMatrix() * glm::mat4(glm::mat3(m_camera->getViewMatrix())));

		//model
		m_modelShader->use();
		m_modelShader->setMat4("Projection", m_camera->getProjectionMatrix());
		m_modelShader->setMat4("View", m_camera->getViewMatrix());
		m_modelShader->setVec3("viewPos", m_camera->getPosition());
		m_modelShader->setVec3("lightDirection", guiVals.lightDir);
		m_modelShader->setVec3("lightColour", guiVals.lightCol);
		m_vampire->renderModel(m_modelShader);

		m_billboard->render(m_camera, guiVals.scale);

		//floor
		// Scene Data - Lights, Camera
		m_floorShader->use();
		m_floorShader->setMat4("projection", m_camera->getProjectionMatrix());
		m_floorShader->setMat4("view", m_camera->getViewMatrix());
		m_floorShader->setMat4("model", glm::mat4(1.0f));
		m_floorShader->setVec3("viewPos", m_camera->getPosition());
		m_floorShader->setFloat("hmScale", guiVals.hmScale);
		//
		m_floorShader->setVec3("floorCol", guiVals.floorCol);
		m_floorShader->setVec3("lightDirection", guiVals.lightDir);
		m_floorShader->setVec3("lightColour", guiVals.lightCol);

		m_floorShader->setBool("cdm", guiVals.cdm);

		m_terrain->setHeightMapUniform(m_floorShader);

		

		//draw
		glBindVertexArray(m_terrain->getVAO());
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_PATCHES, 0, m_terrain->getSize());

		m_particleSystem->render(m_camera);
	}
	else
	{
		//m_textureCompute->use();
		//m_textureCompute->setInt("inputImg", m_terrain->getHeightMap());
		//m_textureCompute->setVec3("col", glm::vec3(1.0, 0.0, 1.0));

		m_noiseCompute->use();
		m_noiseCompute->setInt("octaves", guiVals.octaves);
		m_noiseCompute->setInt("noiseFMB", guiVals.noiseType);
		m_noiseCompute->setFloat("frequency", guiVals.frequency);
		m_noiseCompute->setFloat("amplitude", guiVals.amplitude);
		m_noiseCompute->setFloat("lacunarity", guiVals.lacunarity);
		m_noiseCompute->setFloat("persistence", guiVals.persistence);
		glBindImageTexture(0, m_emptyTexture->getID(), 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
		glDispatchCompute((GLuint)16, (GLuint)32, 1);
		glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
		m_textureViewer->drawColourTexture(m_emptyTexture->getID());
	}

}


