
#include "../include/appNative.hpp"
#include <iostream>


AppNative::AppNative(int width, int height, const char* title) :
window_size(width, height)
{
  if (!glfwInit()) {
    exit(1);
  }

  window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    exit(1);
  }
}

AppNative::~AppNative() {
  glfwTerminate();
}

void AppNative::setup() {
  // set pointer to glfw
  glfwSetWindowUserPointer(window, this);

  glfwMakeContextCurrent(window);
  
  glfwSetKeyCallback        (window, keyCallBack);
  glfwSetCursorPosCallback  (window, mousePositionCallBack);
  glfwSetMouseButtonCallback(window, mouseButtonCallBack);
}

bool AppNative::isOpen() {
  return !glfwWindowShouldClose(window);
}

void AppNative::clearWindowBuff() {
  glClear(GL_COLOR_BUFFER_BIT);
}

void AppNative::updateEvent() {
  key_event.clear();
  mouse_event.clear();
  glfwSwapBuffers(window);
  glfwPollEvents();
}


void AppNative::setClearColor(const Color& color) {
  glClearColor(color.r, color.g, color.b, color.a);
}

const vec2i& AppNative::windowSize() const {
  return window_size;
}


bool AppNative::isPushKey(int key) { return key_event.isPush(key); }
bool AppNative::isPullKey(int key) { return key_event.isPull(key); }
bool AppNative::isPressKey(int key) { return key_event.isPress(key); }

bool AppNative::isPushButton(int button) { return mouse_event.isPush(button); }
bool AppNative::isPullButton(int button) { return mouse_event.isPull(button); }
bool AppNative::isPressButton(int button) { return mouse_event.isPress(button); }

const vec2d& AppNative::getMousePos() const { return mouse_event.getPos(); }


void AppNative::keyCallBack(GLFWwindow* window,
                            const int key,    const int scancode,
                            const int action, const int mods)
{
  auto native = (AppNative*)glfwGetWindowUserPointer(window);
  
  if (action == GLFW_PRESS) {
    native->key_event.setKeyPush(key);
    native->key_event.setKeyPress(key);
  }
  if (action == GLFW_RELEASE) {
    native->key_event.setKeyPull(key);
    native->key_event.popKeyPress(key);
  }
}

void AppNative::mouseButtonCallBack(GLFWwindow* window,
                                    int button, int action, int mods)
{
  auto native = (AppNative*)glfwGetWindowUserPointer(window);

  if (action == GLFW_PRESS) {
    native->mouse_event.setButtonPush(button);
    native->mouse_event.setButtonPress(button);
  }
  if (action == GLFW_RELEASE) {
    native->mouse_event.setButtonPull(button);
    native->mouse_event.popButtonPress(button);
  }
}

void AppNative::mousePositionCallBack(GLFWwindow* window,
                                      double xpos, double ypos)
{ 
  auto native = (AppNative*)glfwGetWindowUserPointer(window);

  native->mouse_event.setMousePos(xpos, ypos);
}
