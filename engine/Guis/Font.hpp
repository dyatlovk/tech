#pragma once

#include <memory>

#include "Imgui.hpp"
#include "Resources/Resource.hpp"

namespace mtEngine
{
  class Font : public Resource
  {
  public:
    using FontPtr = std::shared_ptr<Font>;
    Font();

    static FontPtr Load(const std::string &name, const std::string &path, float size, const ImFontConfig *config, const ImWchar ranges[]);

    ImFont *GetFont() { return _font; }

    [[nodiscard]] std::type_index GetTypeIndex() const override
    {
      return typeid(Font);
    }

  private:
    ImFont *load(const std::string &path, float size, const ImFontConfig *config, const ImWchar ranges[]);
    ImFont *_font;
  };
} // namespace mtEngine
