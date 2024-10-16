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

		m_flameTexture = std::make_shared<Texture>("..\\Resources\\flame.png");

		m_particleSystem = std::make_shared<ParticleSystem>(glm::vec3(0.f, 10.f, 0.f), 5000, m_flameTexture, 2);

		m_waterQuad = std::make_shared<WaterQuad>();

		m_flatColShader = std::make_shared<Shader>("..\\Shaders\\waterVert.glsl", "..\\Shaders\\waterFrag.glsl");

		FBOrefraction = std::make_shared<FrameBuffer>(1, true);
		FBOreflection = std::make_shared<FrameBuffer>(1, true);

		m_dudvMap = std::make_shared<Texture>("..\\Resources\\waterDUDV.png");
		m_waterNormalMap = std::make_shared<Texture>("..\\Resources\\waterNormals.png");
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
	m_particleSystem->update(guiVals);
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

		glEnable(GL_CLIP_DISTANCE0);


		FBOrefraction->bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_floorShader->use();
		m_floorShader->setVec4("plane", glm::vec4(0, -1, 0, 1.f));
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

		glBindVertexArray(m_terrain->getVAO());
		glDrawArrays(GL_PATCHES, 0, m_terrain->getSize());
	

		FBOrefraction->bindDefault();
		FBOrefraction->clear();

		FBOreflection->bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float dist = 2 * (m_camera->getPosition().y - 1.f);
		m_camera->getPosition().y -= dist;
		m_camera->inversePitch();
		m_camera->updateCameraVectors();
		m_floorShader->use();
		m_floorShader->setVec4("plane", glm::vec4(0, 1, 0, -1.f));
		glBindVertexArray(m_terrain->getVAO());
		glDrawArrays(GL_PATCHES, 0, m_terrain->getSize());
		
		m_camera->getPosition().y += dist;
		m_camera->inversePitch();
		m_camera->updateCameraVectors();

		FBOreflection->bindDefault();
		FBOreflection->clear();

		glDisable(GL_CLIP_DISTANCE0);

		m_flatColShader->use();
		m_flatColShader->setMat4("projection", m_camera->getProjectionMatrix());
		m_flatColShader->setMat4("view", m_camera->getViewMatrix());
		m_flatColShader->setFloat("screenW", SCR_WIDTH);
		m_flatColShader->setFloat("screenH",SCR_HEIGHT);
		m_flatColShader->setVec3("UP", m_camera->getUp());
		m_flatColShader->setVec3("viewPos", m_camera->getPosition());
		m_flatColShader->setFloat("time", glfwGetTime());
		m_flatColShader->setFloat("rate", guiVals.rate);
		m_flatColShader->setInt("refraction", 0);
		m_flatColShader->setInt("reflection", 1);
		m_flatColShader->setInt("dudvMap", 2);
		m_flatColShader->setInt("normalMap", 3);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, FBOrefraction->getColourAttachment());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, FBOreflection->getColourAttachment());
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, m_dudvMap->getID());
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, m_waterNormalMap->getID());

		glBindVertexArray(m_waterQuad->getVAO());
		glDrawArrays(GL_TRIANGLES,0, m_waterQuad->getSize());

		//

		//model
		m_modelShader->use();
		m_modelShader->setMat4("Projection", m_camera->getProjectionMatrix());
		m_modelShader->setMat4("View", m_camera->getViewMatrix());
		m_modelShader->setVec3("viewPos", m_camera->getPosition());
		m_modelShader->setVec3("lightDirection", guiVals.lightDir);
		m_modelShader->setVec3("lightColour", guiVals.lightCol);
		m_vampire->renderModel(m_modelShader);

		m_billboard->render(m_camera, guiVals.scale);

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


