#include "Transform.hpp"

namespace mtEngine
{
  Transform::Transform(const glm::vec3 &translation, const glm::vec4 &rotation, const glm::vec3 &scale)
      : m_translation(translation)
      , m_rotation(rotation)
      , m_scale(scale)
      , _mvp(glm::mat4(1.0f))
  {
    UpdateMatrix();
  }

  void Transform::UpdateMatrix()
  {
    _mvp = glm::translate(_mvp, m_translation);

    mtEngine::mtVec4f rot = {(float)m_rotation.x, (float)m_rotation.y, (float)m_rotation.z, (float)m_rotation.w};
    mtEngine::quatToAxisAngle q;
    q = rot;
    _mvp = glm::rotate(_mvp, glm::radians(q.angle), glm::vec3(q.x, q.y, q.z));
    _mvp = glm::scale(_mvp, m_scale);
  }

  auto Transform::SetTranslation(const double x, const double y, const double z) -> void
  {
    m_translation = glm::vec3(x, y, z);
  }
} // namespace mtEngine
