#pragma once

#include <chrono>
#include <vector>

#include "Guis/Imgui.hpp"
namespace Game
{
  class Message
  {
  public:
    static constexpr uint64_t SHOW_TIME = 5000; //visible time in ms
    Message(const std::string &text, float duration) : duration(SHOW_TIME)
    {
      this->creation_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()) .count();
      this->content = text;
      this->duration = duration;
    }

    inline uint64_t GetElapsedTime() const
    {
      uint64_t tick = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()) .count();
      return tick - this->creation_time;
    }

    bool const isExpired()
    {
      const auto elapsed = GetElapsedTime();
      if (elapsed > this->duration) return true;
      return false;
    }

    const std::string *GetContent()
    {
        return &this->content;
    }

  private:
    std::string content;
    uint64_t duration = SHOW_TIME;
    uint64_t creation_time = 0;
  };

  class Notify
  {
  public:
    Notify();

    ~Notify()
    {
        ShutDown();
    }

    void Add(const Message &msg)
    {
        notifications.push_back(msg);
    }

    void Render();

    void Remove(int index);

    void ShutDown()
    {
        notifications.clear();
    }

  private:
    // start from bottom of the screen
    ImVec2 startPos;
    std::vector<Message> notifications;

private:
    void RenderMessages();
  };
} // namespace Game
