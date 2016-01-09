
#include "key.hpp"


Key::Key() :
push(0), 
pull(0),
press(0) {}


void Key::update(GLFWwindow* window) {
  int key_w = glfwGetKey(window, GLFW_KEY_W);
  int key_a = glfwGetKey(window, GLFW_KEY_A);
  int key_s = glfwGetKey(window, GLFW_KEY_S);
  int key_d = glfwGetKey(window, GLFW_KEY_D);
  int key_z = glfwGetKey(window, GLFW_KEY_Z);
  int key_x = glfwGetKey(window, GLFW_KEY_X);
  int key_e = glfwGetKey(window, GLFW_KEY_E);
  int key_esc = glfwGetKey(window, GLFW_KEY_ESCAPE);
  
  char _press = 0;
  if (key_w == GLFW_PRESS) _press |= Keys::W;
  if (key_a == GLFW_PRESS) _press |= Keys::A;
  if (key_s == GLFW_PRESS) _press |= Keys::S;
  if (key_d == GLFW_PRESS) _press |= Keys::D;
  if (key_z == GLFW_PRESS) _press |= Keys::Z;
  if (key_x == GLFW_PRESS) _press |= Keys::X;
  if (key_e == GLFW_PRESS) _press |= Keys::E;
  if (key_esc == GLFW_PRESS) _press |= Keys::Esc;

  push  = _press & ~press;
  pull  = ~_press & press;
  press = _press;
}

bool Key::isPush(Keys key) const {
  return push & key;
}

bool Key::isPull(Keys key) const {
  return pull & key;
}

bool Key::isPress(Keys key) const {
  return press & key;
}
