
#include "mouse.hpp"
#include "../window/window.hpp"


Mouse::Mouse() :
pos(0.0, 0.0),
push(0),
pull(0),
press(0) {}


Eigen::Vector2d Mouse::getPos() const {
  return pos;
}

void Mouse::update(GLFWwindow* window) {
  // Cursor Pos
  glfwGetCursorPos(window, &pos.x(), &pos.y());
  pos.x() -= getWindowWidth() * 0.5f;
  pos.y() = -pos.y() + getWindowHeight() * 0.5f;

  // Button
  left  = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
  right = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

  char _press = 0;
  if (left  == GLFW_PRESS) _press |= Button::Left;
  if (right == GLFW_PRESS) _press |= Button::Right;

  push  = _press & ~press;
  pull  = ~_press & press;
  press = _press;
}

bool Mouse::isPush(Button button) const {
  return push & button;
}

bool Mouse::isPull(Button button) const {
  return pull & button;
}

bool Mouse::isPress(Button button) const {
  return press & button;
}
