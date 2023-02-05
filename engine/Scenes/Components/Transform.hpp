#pragma once

#include <Maths/Transformation.hpp>

#include "Resources/Resource.hpp"
#include "Scenes/Component.hpp"
#include "third_party/glm/ext/matrix_float4x4.hpp"
#include "third_party/glm/ext/matrix_transform.hpp"
#include "third_party/glm/ext/vector_float3.hpp"

namespace mtEngine
{
  class Transform : public Component::Registrar<Transform>, public Resource
  {
    inline static const bool Registered = Register("transform");

  public:
    Transform() = default;
    Transform(const glm::vec3 &translation, const glm::vec4 &rotation, const glm::vec3 &scale);

    [[nodiscard]] std::type_index GetTypeIndex() const override { return typeid(Transform); }

    const glm::mat4 &GetWorldMatrix() { return _mvp; }

    const glm::vec3 &GetTranslation() { return m_translation; };
    const glm::vec4 &GetRotation() { return m_rotation; };
    const glm::vec3 &GetScale() { return m_scale; };

    auto SetTranslation(const double x = 0, const double y = 0, const double z = 0) -> void;

  private:
    glm::vec3 m_translation{};
    glm::vec4 m_rotation{};
    glm::vec3 m_scale{};

  private:
    void UpdateMatrix();
    glm::mat4 _mvp{};
  };
} // namespace mtEngine
