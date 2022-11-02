#include "FPSCamera.hpp"

namespace Game
{
  FPSCamera::FPSCamera()
      : firstMouse(true)
      , MovementSpeed(10.0f)
      , MouseSensitivity(0.05f)
      , Right(glm::vec3(1.0f, 0.0f, 0.0f))
      , Up(glm::vec3(0.0f, 1.0f, 0.0f))
      , Front(0.0f, 0.0f, -1.0f)
      , WorldUp(Up)
      , Yaw(-90.0f)
      , Pitch(0.0f)
  {
    Mouse::Get()->HideCursor();
    UpdateCameraVectors();
    MouseCallback();
  }

  void FPSCamera::Start() {}

  void FPSCamera::Update()
  {
    auto delta = mtEngine::Engine::Get()->GetDelta().AsSeconds();
    auto window = Window::Get();
    auto mouse = Mouse::Get();

    if (!Scenes::Get()->IsPaused())
    {
      ProcessInput();
      projectionMatrix = glm::perspective(glm::radians(fieldOfView), window->GetAspectRatio(), nearPlane, farPlane);
      viewMatrix = glm::lookAt(position, position + Front, Up);
    }
  }

  void FPSCamera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
  {
    float vel = MovementSpeed * deltaTime;

    if (direction == FORWARD)
      position += Front * vel;
    if (direction == BACKWARD)
      position -= Front * vel;
    if (direction == LEFT)
      position -= Right * vel;
    if (direction == RIGHT)
      position += Right * vel;
  }

  void FPSCamera::ProcessInput()
  {
    auto delta = mtEngine::Engine::Get()->GetDelta().AsSeconds();
    auto window = Window::Get()->GetWindow();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      ProcessKeyboard(FORWARD, delta);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      ProcessKeyboard(BACKWARD, delta);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
      ProcessKeyboard(LEFT, delta);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
      ProcessKeyboard(RIGHT, delta);
  }

  void FPSCamera::UpdateCameraVectors()
  {
    // Вычисляем новый вектор-прямо
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    // Также пересчитываем вектор-вправо и вектор-вверх
    Right = glm::normalize(glm::cross(Front, WorldUp)); // Нормализуем векторы, потому что их длина становится
    // стремится к 0 тем больше, чем больше вы смотрите вверх или
    // вниз, что приводит к более медленному движению.
    Up = glm::normalize(glm::cross(Right, Front));
  }

  void FPSCamera::MouseCallback()
  {
    auto mouse = mtEngine::Mouse::Get();

    mouse->onPositionEvent.Add([this](double x, double y){
      if (firstMouse) {
        lastX = x;
        lastY = y;
        firstMouse = false;
      }

      double xoffset = x - lastX;
      double yoffset = lastY - y; // reversed since y-coordinates go from bottom to top

      lastX = x;
      lastY = y;

      ProcessMouseMovement(xoffset, yoffset);
    });
  }

  void FPSCamera::ProcessMouseMovement(double xoffset, double yoffset, GLboolean constrainPitch)
  {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // Убеждаемся, что когда тангаж выходит за пределы обзора, экран не
    // переворачивается
    if (constrainPitch)
    {
      if (Pitch > 89.0f)
        Pitch = 89.0f;
      if (Pitch < -89.0f)
        Pitch = -89.0f;
    }

    // Обновляем значения вектора-прямо, вектора-вправо и вектора-вверх,
    // используя обновленные значения углов Эйлера
    UpdateCameraVectors();
  }
}; // namespace Game
