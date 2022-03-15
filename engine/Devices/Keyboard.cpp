#include "Keyboard.hpp"
#include <iostream>

#include <GLFW/glfw3.h>

namespace mtEngine {
  static_assert(GLFW_KEY_LAST == static_cast<int16_t>(Key::Last), "GLFW keys count does not match our keys enum count.");

  void CallbackKey(GLFWwindow *window, int32_t key, int32_t scancode, int32_t action, int32_t mods) {
    Keyboard::Get()->onKey(static_cast<Key>(key), static_cast<InputAction>(action), InputMod(mods));
  }

  void CallbackChar(GLFWwindow *window, uint32_t codepoint) {
    Keyboard::Get()->onChar(static_cast<char>(codepoint));
  }

  Keyboard::Keyboard() {
    glfwSetKeyCallback(Window::Get()->GetWindow(), CallbackKey);
    glfwSetCharCallback(Window::Get()->GetWindow(), CallbackChar);
  }

  void Keyboard::Update() {
  }

  InputAction Keyboard::GetKey(Key key) const {
    auto state = glfwGetKey(Window::Get()->GetWindow(), static_cast<int32_t>(key));
    return static_cast<InputAction>(state);
  }

  Key Keyboard::FromString(const std::string &name)
  {
    if(name == "Space") {
      return Key::Space;
    }
    if(name == "Apostrophe") {
      return Key::Apostrophe;
    }
    if(name == "Comma") {
      return Key::Comma;
    }
    if(name == "Minus") {
      return Key::Minus;
    }
    if(name == "Period") {
      return Key::Period;
    }
    if(name == "Slash") {
      return Key::Slash;
    }
    if(name == "0") {
      return Key::_0;
    }
    if(name == "1") {
      return Key::_1;
    }
    if(name == "2") {
      return Key::_2;
    }
    if(name == "3") {
      return Key::_3;
    }
    if(name == "4") {
      return Key::_4;
    }
    if(name == "5") {
      return Key::_5;
    }
    if(name == "6") {
      return Key::_6;
    }
    if(name == "7") {
      return Key::_7;
    }
    if(name == "8") {
      return Key::_8;
    }
    if(name == "9") {
      return Key::_9;
    }
    if(name == "Semicolon") {
      return Key::Semicolon;
    }
    if(name == "Equal") {
      return Key::Equal;
    }
    if(name == "A") {
      return Key::A;
    }
    if(name == "B") {
      return Key::B;
    }
    if(name == "C") {
      return Key::C;
    }
    if(name == "D") {
      return Key::D;
    }
    if(name == "E") {
      return Key::E;
    }
    if(name == "F") {
      return Key::F;
    }
    if(name == "G") {
      return Key::G;
    }
    if(name == "H") {
      return Key::H;
    }
    if(name == "I") {
      return Key::I;
    }
    if(name == "J") {
      return Key::J;
    }
    if(name == "K") {
      return Key::K;
    }
    if(name == "L") {
      return Key::L;
    }
    if(name == "M") {
      return Key::M;
    }
    if(name == "N") {
      return Key::N;
    }
    if(name == "O") {
      return Key::O;
    }
    if(name == "P") {
      return Key::P;
    }
    if(name == "Q") {
      return Key::Q;
    }
    if(name == "R") {
      return Key::R;
    }
    if(name == "S") {
      return Key::S;
    }
    if(name == "T") {
      return Key::T;
    }
    if(name == "U") {
      return Key::U;
    }
    if(name == "V") {
      return Key::V;
    }
    if(name == "W") {
      return Key::W;
    }
    if(name == "X") {
      return Key::X;
    }
    if(name == "Y") {
      return Key::Y;
    }
    if(name == "Z") {
      return Key::Z;
    }
    if(name == "LeftBracket") {
      return Key::LeftBracket;
    }
    if(name == "Backslash") {
      return Key::Backslash;
    }
    if(name == "RightBracket") {
      return Key::RightBracket;
    }
    if(name == "GraveAccent") {
      return Key::GraveAccent;
    }
    if(name == "World1") {
      return Key::World1;
    }
    if(name == "World2") {
      return Key::World2;
    }
    if(name == "Escape") {
      return Key::Escape;
    }
    if(name == "Enter") {
      return Key::Enter;
    }
    if(name == "Tab") {
      return Key::Tab;
    }
    if(name == "Backspace") {
      return Key::Backspace;
    }
    if(name == "Insert") {
      return Key::Insert;
    }
    if(name == "Delete") {
      return Key::Delete;
    }
    if(name == "Right") {
      return Key::Right;
    }
    if(name == "Left") {
      return Key::Left;
    }
    if(name == "Down") {
      return Key::Down;
    }
    if(name == "Up") {
      return Key::Up;
    }
    if(name == "PageUp") {
      return Key::PageUp;
    }
    if(name == "PageDown") {
      return Key::PageDown;
    }
    if(name == "Home") {
      return Key::Home;
    }
    if(name == "End") {
      return Key::End;
    }
    if(name == "CapsLock") {
      return Key::CapsLock;
    }
    if(name == "ScrollLock") {
      return Key::ScrollLock;
    }
    if(name == "NumLock") {
      return Key::NumLock;
    }
    if(name == "PrintScreen") {
      return Key::PrintScreen;
    }
    if(name == "Pause") {
      return Key::Pause;
    }
    if(name == "F1") {
      return Key::F1;
    }
    if(name == "F2") {
      return Key::F2;
    }
    if(name == "F3") {
      return Key::F3;
    }
    if(name == "F4") {
      return Key::F4;
    }
    if(name == "F5") {
      return Key::F5;
    }
    if(name == "F6") {
      return Key::F6;
    }
    if(name == "F7") {
      return Key::F7;
    }
    if(name == "F8") {
      return Key::F8;
    }
    if(name == "F9") {
      return Key::F9;
    }
    if(name == "F10") {
      return Key::F10;
    }
    if(name == "F11") {
      return Key::F11;
    }
    if(name == "F12") {
      return Key::F12;
    }
    if(name == "F13") {
      return Key::F13;
    }
    if(name == "F14") {
      return Key::F14;
    }
    if(name == "F15") {
      return Key::F15;
    }
    if(name == "F16") {
      return Key::F16;
    }
    if(name == "F17") {
      return Key::F17;
    }
    if(name == "F18") {
      return Key::F18;
    }
    if(name == "F19") {
      return Key::F19;
    }
    if(name == "F20") {
      return Key::F20;
    }
    if(name == "F21") {
      return Key::F21;
    }
    if(name == "F22") {
      return Key::F22;
    }
    if(name == "F23") {
      return Key::F23;
    }
    if(name == "F24") {
      return Key::F24;
    }
    if(name == "F25") {
      return Key::F25;
    }
    if(name == "Numpad0") {
      return Key::Numpad0;
    }
    if(name == "Numpad1") {
      return Key::Numpad1;
    }
    if(name == "Numpad2") {
      return Key::Numpad2;
    }
    if(name == "Numpad3") {
      return Key::Numpad3;
    }
    if(name == "Numpad4") {
      return Key::Numpad4;
    }
    if(name == "Numpad5") {
      return Key::Numpad5;
    }
    if(name == "Numpad6") {
      return Key::Numpad6;
    }
    if(name == "Numpad7") {
      return Key::Numpad7;
    }
    if(name == "Numpad8") {
      return Key::Numpad8;
    }
    if(name == "Numpad9") {
      return Key::Numpad9;
    }
    if(name == "NumpadDecimal") {
      return Key::NumpadDecimal;
    }
    if(name == "NumpadDivide") {
      return Key::NumpadDivide;
    }
    if(name == "NumpadMultiply") {
      return Key::NumpadMultiply;
    }
    if(name == "NumpadSubtract") {
      return Key::NumpadSubtract;
    }
    if(name == "NumpadAdd") {
      return Key::NumpadAdd;
    }
    if(name == "NumpadEnter") {
      return Key::NumpadEnter;
    }
    if(name == "NumpadEqual") {
      return Key::NumpadEqual;
    }
    if(name == "ShiftLeft") {
      return Key::ShiftLeft;
    }
    if(name == "ControlLeft") {
      return Key::ControlLeft;
    }
    if(name == "AltLeft") {
      return Key::AltLeft;
    }
    if(name == "SuperLeft") {
      return Key::SuperLeft;
    }
    if(name == "ShiftRight") {
      return Key::ShiftRight;
    }
    if(name == "ControlRight") {
      return Key::ControlRight;
    }
    if(name == "AltRight") {
      return Key::AltRight;
    }
    if(name == "SuperRight") {
      return Key::SuperRight;
    }
    if(name == "Menu") {
      return Key::Menu;
    }

    return Key::Unknown;
  }

  std::string Keyboard::ToString(Key key) {
    switch (key) {
      case Key::Space:
        return "Space";
      case Key::Apostrophe:
        return "Apostrophe";
      case Key::Comma:
        return "Comma";
      case Key::Minus:
        return "Minus";
      case Key::Period:
        return "Period";
      case Key::Slash:
        return "Slash";
      case Key::_0:
        return "0";
      case Key::_1:
        return "1";
      case Key::_2:
        return "2";
      case Key::_3:
        return "3";
      case Key::_4:
        return "4";
      case Key::_5:
        return "5";
      case Key::_6:
        return "6";
      case Key::_7:
        return "7";
      case Key::_8:
        return "8";
      case Key::_9:
        return "9";
      case Key::Semicolon:
        return "Semicolon";
      case Key::Equal:
        return "Equal";
      case Key::A:
        return "A";
      case Key::B:
        return "B";
      case Key::C:
        return "C";
      case Key::D:
        return "D";
      case Key::E:
        return "E";
      case Key::F:
        return "F";
      case Key::G:
        return "G";
      case Key::H:
        return "H";
      case Key::I:
        return "I";
      case Key::J:
        return "J";
      case Key::K:
        return "K";
      case Key::L:
        return "L";
      case Key::M:
        return "M";
      case Key::N:
        return "N";
      case Key::O:
        return "O";
      case Key::P:
        return "P";
      case Key::Q:
        return "Q";
      case Key::R:
        return "R";
      case Key::S:
        return "S";
      case Key::T:
        return "T";
      case Key::U:
        return "U";
      case Key::V:
        return "V";
      case Key::W:
        return "W";
      case Key::X:
        return "X";
      case Key::Y:
        return "Y";
      case Key::Z:
        return "Z";
      case Key::LeftBracket:
        return "Left Bracket";
      case Key::Backslash:
        return "Backslash";
      case Key::RightBracket:
        return "Right Bracket";
      case Key::GraveAccent:
        return "Grave Accent";
      case Key::World1:
        return "World1";
      case Key::World2:
        return "World2";
      case Key::Escape:
        return "Escape";
      case Key::Enter:
        return "Enter";
      case Key::Tab:
        return "Tab";
      case Key::Backspace:
        return "Backspace";
      case Key::Insert:
        return "Insert";
      case Key::Delete:
        return "Delete";
      case Key::Right:
        return "Right";
      case Key::Left:
        return "Left";
      case Key::Down:
        return "Down";
      case Key::Up:
        return "Up";
      case Key::PageUp:
        return "Page Up";
      case Key::PageDown:
        return "Page Down";
      case Key::Home:
        return "Home";
      case Key::End:
        return "End";
      case Key::CapsLock:
        return "Caps Lock";
      case Key::ScrollLock:
        return "Scroll Lock";
      case Key::NumLock:
        return "Num Lock";
      case Key::PrintScreen:
        return "Print Screen";
      case Key::Pause:
        return "Pause";
      case Key::F1:
        return "F1";
      case Key::F2:
        return "F2";
      case Key::F3:
        return "F3";
      case Key::F4:
        return "F4";
      case Key::F5:
        return "F5";
      case Key::F6:
        return "F6";
      case Key::F7:
        return "F7";
      case Key::F8:
        return "F8";
      case Key::F9:
        return "F9";
      case Key::F10:
        return "F10";
      case Key::F11:
        return "F11";
      case Key::F12:
        return "F12";
      case Key::F13:
        return "F13";
      case Key::F14:
        return "F14";
      case Key::F15:
        return "F15";
      case Key::F16:
        return "F16";
      case Key::F17:
        return "F17";
      case Key::F18:
        return "F18";
      case Key::F19:
        return "F19";
      case Key::F20:
        return "F20";
      case Key::F21:
        return "F21";
      case Key::F22:
        return "F22";
      case Key::F23:
        return "F23";
      case Key::F24:
        return "F24";
      case Key::F25:
        return "F25";
      case Key::Numpad0:
        return "Numpad 0";
      case Key::Numpad1:
        return "Numpad 1";
      case Key::Numpad2:
        return "Numpad 2";
      case Key::Numpad3:
        return "Numpad 3";
      case Key::Numpad4:
        return "Numpad 4";
      case Key::Numpad5:
        return "Numpad 5";
      case Key::Numpad6:
        return "Numpad 6";
      case Key::Numpad7:
        return "Numpad 7";
      case Key::Numpad8:
        return "Numpad 8";
      case Key::Numpad9:
        return "Numpad 9";
      case Key::NumpadDecimal:
        return "Numpad Decimal";
      case Key::NumpadDivide:
        return "Numpad Divide";
      case Key::NumpadMultiply:
        return "Numpad Multiply";
      case Key::NumpadSubtract:
        return "Numpad Subtract";
      case Key::NumpadAdd:
        return "Numpad Add";
      case Key::NumpadEnter:
        return "Numpad Enter";
      case Key::NumpadEqual:
        return "Numpad Equal";
      case Key::ShiftLeft:
        return "Shift Left";
      case Key::ControlLeft:
        return "Control Left";
      case Key::AltLeft:
        return "Alt Left";
      case Key::SuperLeft:
        return "Super Left";
      case Key::ShiftRight:
        return "Shift Right";
      case Key::ControlRight:
        return "Control Right";
      case Key::AltRight:
        return "Alt Right";
      case Key::SuperRight:
        return "Super Right";
      case Key::Menu:
        return "Menu";
      default:
        return "Undefined";
    }
  }
}

