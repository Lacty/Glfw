
#pragma once
#include <GLFW/glfw3.h>
#include <Eigen/Core>


enum Button {
  Left  = 1 << 0,
  Right = 1 << 1
};

class Mouse {
private:
  Eigen::Vector2d pos;

  int left;
  int right;

  char push;
  char pull;
  char press;

public:
  Mouse();

  Eigen::Vector2d getPos() const;

  void update(GLFWwindow* window);

  bool isPush(Button button) const;
  bool isPull(Button button) const;
  bool isPress(Button button) const;
};
