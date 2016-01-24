
#pragma once
#include <set>
#include <GLFW/glfw3.h>
#include "vector.hpp"


class Mouse {
private:
  vec2d pos;

  std::set<int> push;
  std::set<int> pull;
  std::set<int> press;

public:
  Mouse() :pos(0, 0) {};

  // this class can't copy
  Mouse(const Mouse&) = delete;
  Mouse& operator =(const Mouse&) = delete;

  void clear() {
    push.clear();
    pull.clear();
  }

  void setButtonPush(int button) { push.emplace(button); }
  void setButtonPull(int button) { pull.emplace(button); }
  void setButtonPress(int button) { press.emplace(button); }

  void popButtonPress(int button) { press.erase(press.find(button)); }

  void setMousePos(GLFWwindow* window) 
  {
    glfwGetCursorPos(window, &pos[0], &pos[1]);
  }

  bool isPush(int button) {
    if (push.find(button) == push.end()) return false;
    push.erase(push.find(button));
    return true;
  }

  bool isPull(int button) {
    if (pull.find(button) == pull.end()) return false;
    pull.erase(pull.find(button));
    return true;
  }

  bool isPress(int button) {
    if (press.find(button) == press.end()) return false;
    return true;
  }

  const vec2d& getPos() const { return pos; }
};
