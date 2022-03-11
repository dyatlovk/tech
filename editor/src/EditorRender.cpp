#include "EditorRender.hpp"
#include "Devices/Window.hpp"
#include "Graphics/Graphics.hpp"
#include <iostream>

namespace Editor {
  EditorRender::EditorRender() {
    std::cout << "start editor renderer" << std::endl;
  };

  EditorRender::~EditorRender() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
  };

  void EditorRender::Start()
  {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking

    const char* glsl_version = "#version 130";
    auto window = Window::Get()->GetWindow();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
  }

  void EditorRender::Update()
  {
    bool show_demo_window = true;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::ShowDemoWindow(&show_demo_window);
    ImGui::Render();

    auto window = mtEngine::Window::Get()->GetWindow();
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    glfwSwapBuffers(window);
  }
}
