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
    Light(const glm::vec3 &color, const int size = -1, const float strength = 1.0f, const glm::vec3 &direction = glm::vec3(0.0, 0.0, 0.0));
    void Start() override;
    void Update() override;

    auto GetDirection() -> const glm::vec3 { return m_direction ; };
    auto GetColor()     -> const glm::vec3 { return m_color     ; };
    auto GetSize()      -> const int       { return m_size      ; };
    auto GetStrength()  -> const float     { return m_strength  ; };

  private:
    int m_size;
    glm::vec3 m_color;
    glm::vec3 m_direction;
    float m_strength;
  };
} // namespace mtEngine
