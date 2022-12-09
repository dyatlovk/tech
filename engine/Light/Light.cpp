#include "Light.hpp"

namespace mtEngine
{
  Light::Light(const glm::vec3 &color, const int size, const float strength, const glm::vec3 &direction)
      : m_color(color)
      , m_size(size)
      , m_strength(strength)
      , m_direction(direction){};

  void Light::Start() {}

  void Light::Update() {}
} // namespace mtEngine
