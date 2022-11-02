#pragma once

#include <Devices/Mouse.hpp>
#include <Devices/Keyboard.hpp>
#include <Scenes/Camera.hpp>
#include <Scenes/Scenes.hpp>

namespace Game
{
  using namespace mtEngine;

  enum Camera_Movement
  {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
  };

  class FPSCamera : public Camera
  {
  public:
    FPSCamera();
    void Start() override;
    void Update() override;

  private:
    bool firstMouse;

    glm::vec3 Front{};
    glm::vec3 Up{};
    glm::vec3 Right{};
    glm::vec3 WorldUp{};
    // углы Эйлера
    double Yaw;
    double Pitch;
    // Настройки камеры
    float MovementSpeed;
    double MouseSensitivity;
    float Zoom;
    float m_accelarate;

    double lastX = (double)mtEngine::Window::Get()->GetSize()[0] / 2.0f;
    double lastY = (double)mtEngine::Window::Get()->GetSize()[1] / 2.0f;

  private:
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    void UpdateCameraVectors();
    void ProcessInput();
    void MouseCallback();
    void ProcessMouseMovement(double xoffset, double yoffset, GLboolean constrainPitch = true);

    const float SPEED = 2.5f;
    const float SENSITIVITY = 0.1f;
    const float ZOOM = 45.0f;
    const float horizontalAngle = 3.14f;
    const float accelarate = 3.0f;
  };
}; // namespace Game
