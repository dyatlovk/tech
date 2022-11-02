#pragma once

#include "Maths/Vectors/Matrix4.hpp"
#include "Maths/Vectors/Vector3d.hpp"
#include "Maths/Vectors/Vector3d.hpp"
#include "third_party/glm/gtc/type_ptr.hpp"

namespace mtEngine
{
  class Camera
  {
  public:
    Camera()
        : nearPlane(0.1f)
        , farPlane(1000.0f)
        , fieldOfView(45.0f)
        , position(glm::vec3(0.0f, 0.0f, 0.0f))
        , rotation(glm::vec3(0.0f, 0.0f, 0.0f)){};
    virtual ~Camera() = default;

    virtual void Start() {}
    virtual void Update() {}

    float GetNearPlane() const { return nearPlane; }
    void SetNearPlane(float nearPlane) { this->nearPlane = nearPlane; }

    float GetFarPlane() const { return farPlane; }
    void SetFarPlane(float farPlane) { this->farPlane = farPlane; }

    float GetFieldOfView() const { return fieldOfView; }
    void SetFieldOfView(float fieldOfView) { this->fieldOfView = fieldOfView; }

    const glm::vec3 &GetPosition() const { return position; }
    const glm::vec3 &GetRotation() const { return rotation; }
    const float &GetVelocity() const { return velocity; }

    const glm::mat4 &GetViewMatrix() const { return viewMatrix; }
    const glm::mat4 &GetProjectionMatrix() const { return projectionMatrix; }

  protected:
    float nearPlane, farPlane;
    float fieldOfView;

    glm::vec3 position;
    glm::vec3 rotation;
    float velocity;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
  };
} // namespace mtEngine
