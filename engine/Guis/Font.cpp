#include "Font.hpp"

#include "IconsFontAwesome6.h"
#include "Resources/ResourcesManager.hpp"

namespace mtEngine
{
  Font::Font() = default;

  Font::FontPtr Font::Load(const std::string &name, const std::string &path, float size, const ImFontConfig *config, const ImWchar ranges[])
  {
    auto mgr = ResourcesManager::Get();
    if (auto resource = mgr->find<Font>(name)) return resource;
    auto resource = std::make_shared<Font>();
    resource->load(path, size, config, ranges);
    
    mgr->add(name, std::dynamic_pointer_cast<Resource>(resource));

    return resource;
  }

  ImFont *Font::load(const std::string &path, float size, const ImFontConfig *config, const ImWchar ranges[]) { 
    ImGuiIO &io = ImGui::GetIO(); 
    auto font = io.Fonts->AddFontFromFileTTF(path.c_str(), size, config, ranges);
    _font = font;

    return font;
  }
} // namespace mtEngine
