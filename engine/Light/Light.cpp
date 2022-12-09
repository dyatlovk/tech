#include "Light.hpp"

namespace mtEngine
{
  Light::Light(const std::string &color, const int size, glm::vec3 direction)
      : m_size(size)
      , m_color(color)
      , m_direction(direction){};

  void Light::Start() {}

  void Light::Update() {}
} // namespace mtEngine
