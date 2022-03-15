#include "GameScene.hpp"
#include "Config.hpp"
#include "../States/GameStates.hpp"
#include "Devices/Window.hpp"
#include "Inputs/Input.hpp"

#include "third_party/imgui/imgui.h"
#include "third_party/imgui/imgui_stdlib.h"
#include "third_party/imgui/imgui_impl_glfw.h"
#include "third_party/imgui/imgui_impl_opengl3.h"
#include "third_party/imgui/imgui_internal.h"

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

    std::string p(RESOURCES);
    std::string fontPath = p + "/Game/fonts/Roboto-Regular.ttf";
    io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 17.0f);

    const char* glsl_version = "#version 130";
    auto window = mtEngine::Window::Get()->GetWindow();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border]                 = ImVec4(0.43f, 0.43f, 0.50f, 0.00f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_CheckMark]              = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_Button]                 = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
    colors[ImGuiCol_Header]                 = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_Separator]              = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.18f, 0.35f, 0.58f, 0.86f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.20f, 0.41f, 0.68f, 1.00f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
    colors[ImGuiCol_DockingPreview]         = ImVec4(0.26f, 0.59f, 0.98f, 0.70f);
    colors[ImGuiCol_DockingEmptyBg]         = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
    colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
    colors[ImGuiCol_TableBorderLight]       = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
    colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
   
    Input::Get()->GetButton("Global", "Console")->OnButton().Add([&](InputAction action, InputMod mod) {
      if(InputAction::Press == action) {
        show_console = !show_console;
      };
    });
  }

  void GameScene::BeforeUpdate()
  {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
  }

  void GameScene::Update()
  {
    ImGui::ShowDemoWindow();
    int state = States::Get()->Current();
    Info();

    if(state == GameStates::Inventory) {
      Inventory();
    }

    Console();
  }

  void GameScene::AfterUpdate()
  {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    auto window = mtEngine::Window::Get()->GetWindow();
    glfwSwapBuffers(window);
  }

  void GameScene::Inventory()
  {
    auto viewport = ImGui::GetMainViewport()->Size;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus;
    ImGui::SetNextWindowSize(ImVec2(viewport.x / 100 * 25.0f, viewport.y));
    static bool p_open = true;
    if (ImGui::Begin("Inventory", &p_open, window_flags)) {
      auto window = ImGui::GetCurrentWindow()->Size;
      ImGui::SetWindowPos(ImVec2(viewport.x - window.x, 0.0f));
    }
    ImGui::End();
  }

  void GameScene::Info()
  {
    int state = States::Get()->Current();
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground;
    static bool p_open = true;
    auto viewport = ImGui::GetMainViewport()->Size;
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(ImVec2(viewport.x / 100 * 20.0f, viewport.y));
    if (ImGui::Begin("Left", &p_open, window_flags)) {
      ImGui::Text("%s", GameStates::ToString(state).c_str());
      ImGui::Separator();
      ImGui::Text("%s",   "Console:     ~");
      if(state == GameStates::MainMenu) {
        ImGui::Text("%s", "Start:       Enter");
        ImGui::Text("%s", "Fullscreen:  F");
        ImGui::Text("%s", "Exit:        F10");
      }
      if(state == GameStates::Player) {
        ImGui::Text("%s", "Inventory:  I");
        ImGui::Text("%s", "Pause menu: Esc");
      }
      if(state == GameStates::Inventory) {
        ImGui::Text("%s", "Close: Esc, I");
      }
      if(state == GameStates::PauseMenu) {
        ImGui::Text("%s", "Resume:    Esc");
        ImGui::Text("%s", "Main menu: F10");
      }
    }
    ImGui::End();
  }

  void GameScene::Console()
  {
    if(!show_console) 
    {
      Input::Get()->EnableScheme(true);
      return;
    }
    float height = 45.0f;
    if(show_console) Input::Get()->EnableScheme(false);
    auto viewport = ImGui::GetMainViewport()->Size;
    ImGuiWindowFlags window_flags  = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav;
                     window_flags |= ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
    ImGui::SetNextWindowSize(ImVec2(viewport.x, viewport.y / 100 * height));
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.9f));
    if (ImGui::Begin("Console", &show_console, window_flags)) {
      const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();              // 1 separator, 1 input text
      ImGui::BeginChild("ConsoleContent", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar);  // Leave room for 1 separator + 1 InputText
      if (ImGui::BeginPopupContextWindow())
      {
        ImGui::EndPopup();
      }
      ImGui::TextUnformatted("Console item");
      ImGui::EndChild();
    }

    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
    const char *helperTitle = "##ConsoleInputHelper";
    std::string helperText = ">>";
    float textboxSize = ImGui::CalcTextSize(helperText.c_str()).x + (ImGui::GetStyle().FramePadding.x);
    ImGui::SetNextItemWidth(textboxSize);
    ImGuiInputTextFlags helperFlags = ImGuiInputTextFlags_ReadOnly;
    ImGui::InputText(helperTitle, &helperText, helperFlags); ImGui::SameLine(0.0f, -1.0f);
    ImGui::PopStyleColor();
    
    std::string text = "";
    const char *title = "##ConsoleInput";
    ImGui::SetKeyboardFocusHere();
    ImGuiInputTextFlags inputFlags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
    if (ImGui::InputText(title, &text, inputFlags)) {
    }
    ImGui::End();
    ImGui::PopStyleColor();

    ImGui::End();
    ImGui::PopStyleColor();
  }
}
