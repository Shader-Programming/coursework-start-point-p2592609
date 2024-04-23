#include "Gui.h"


Gui::Gui(GLFWwindow* window) : m_window(window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init();
    ImGui::StyleColorsDark();
}

Gui::~Gui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
}

void Gui::newGuiFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    if(isActive) glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    else glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
}

void Gui::drawGui()
{
    float ms = 1000.0f / ImGui::GetIO().Framerate; ;  //milisecconds
    ImGui::Begin("IMAT3907");
    ImGui::Text("FPS %.3f ms/frame (%.1f FPS)", ms, ImGui::GetIO().Framerate);  // display FPS and ms
    ImGui::Checkbox("Texture View", &guiVals.textureView);
    ImGui::Checkbox("WireFrame", &guiVals.showWireFrame);
    ImGui::Checkbox("CDM", &guiVals.cdm);
    ImGui::SliderFloat("Scale", &guiVals.scale, 0.f, 100.f);
    ImGui::SliderFloat3("Light Dir", (float*)&guiVals.lightDir, -1.0, 1.0);
    ImGui::ColorEdit3("Light Col", (float*)&guiVals.lightCol);
    ImGui::ColorEdit3("Floor Col", (float*)&guiVals.floorCol);
    ImGui::DragFloat("Height Map Scale", &guiVals.hmScale);
    ImGui::SliderFloat("Frequency", &guiVals.frequency, 0.f, 10.f);
    ImGui::SliderFloat("Amplitude", &guiVals.amplitude, 0.f, 10.f);
    ImGui::SliderFloat("Lacunarity", &guiVals.lacunarity, 0.f, 10.f);
    ImGui::SliderFloat("Persistence", &guiVals.persistence, 0.f, 10.f);
    ImGui::SliderInt("Octaves", &guiVals.octaves, 0.f, 10.f);
    ImGui::SliderInt("NoiseType", &guiVals.noiseType, 0.f, 2.f);
    ImGui::SliderFloat("Acceleration", &guiVals.acceleration, 0.f, 100.f);
    ImGui::SliderFloat("Speed", &guiVals.speed, 0.f, 100.f);
    ImGui::SliderFloat("rate", &guiVals.rate, 0.f, 2.f);
    ImGui::ShowDemoWindow();
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
