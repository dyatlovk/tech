#pragma once

#include "Scenes/Component.hpp"
#include "third_party/glm/ext/vector_float3.hpp"

namespace mtEngine
{
  class Light : public Component::Registrar<Light>
  {
    inline static const bool Registered = Register("light");

  public:
    Light() = default;
    Light(const std::string &color, const int size = -1, glm::vec3 direction = glm::vec3(0.0, 0.0, 0.0));
    void Start() override;
    void Update() override;

    auto GetDirection() -> const glm::vec3   { return m_direction ; };
    auto GetColor()     -> const std::string { return m_color     ; };
    auto GetSize()      -> const int         { return m_size      ; };

  private:
    int m_size;
    std::string m_color;
    glm::vec3 m_direction;
  };
} // namespace mtEngine
