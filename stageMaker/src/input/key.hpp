
#pragma once
#include <GLFW/glfw3.h>


enum Keys {
  W = 1 << 0,
  A = 1 << 1,
  S = 1 << 2,
  D = 1 << 3,
  Z = 1 << 4,
  X = 1 << 5,
  Esc = 1 << 6
};

class Key {
private:
  char push;
  char pull;
  char press;

public:
  Key();

  void update(GLFWwindow* window);

  bool isPush(Keys key) const;
  bool isPull(Keys key) const;
  bool isPress(Keys key) const;
};
