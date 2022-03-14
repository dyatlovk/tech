#include "GameScene.hpp"
#include "../States/GameStates.hpp"
#include "Devices/Window.hpp"
#include "third_party/imgui/imgui.h"
#include "third_party/imgui/imgui_impl_glfw.h"
#include "third_party/imgui/imgui_impl_opengl3.h"

using namespace mtEngine;

namespace Game {
  GameScene::GameScene() = default;

  GameScene::~GameScene()
  {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
  };

  void GameScene::Start()
  {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking

    const char* glsl_version = "#version 130";
    auto window = mtEngine::Window::Get()->GetWindow();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
  }

  void GameScene::BeforeUpdate()
  {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
  }

  void GameScene::Update()
  {
    int state = States::Get()->Current();
    static bool show_demo_window = false;
    if(state == GameStates::Inventory) {
      show_demo_window = true;
      ImGui::ShowDemoWindow(&show_demo_window);
    }
  }

  void GameScene::AfterUpdate()
  {
    ImGui::Render();
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    auto window = mtEngine::Window::Get()->GetWindow();
    glfwSwapBuffers(window);
  }
}
