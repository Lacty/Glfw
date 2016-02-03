
#include "../include/appNative.hpp"
#include <iostream>


AppNative::AppNative(int width, int height, const char* title) :
window_size(width, height)
{
  if (!glfwInit()) exit(1);

  window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    exit(1);
  }

  // set pointer to glfw
  glfwSetWindowUserPointer(window, this);

  // make window
  glfwMakeContextCurrent(window);

  // set Viewport
  std::cout << "window size\n" << window_size << std::endl;
  glViewport(0, 0, window_size.x(), window_size.y());
  
  // set callback func
  glfwSetKeyCallback        (window, keyCallBack);
  glfwSetCursorPosCallback  (window, mousePositionCallBack);
  glfwSetMouseButtonCallback(window, mouseButtonCallBack);
  glfwSetScrollCallback     (window, (GLFWscrollfun)     TwEventMouseWheelGLFW3);
  glfwSetCharCallback       (window, (GLFWcharfun)       TwEventCharGLFW3);
  glfwSetWindowSizeCallback (window, windowSizeCallback);
  TwInit(TW_OPENGL, nullptr);
  TwWindowSize(window_size.x(), window_size.y());

  // init camera
  camera = Camera(vec3f(0, 0, 0), vec3f(0, 0, -1));
  camera.setWindowSize(window_size);
  camera.registerTw();
}

AppNative::~AppNative() {
  TwTerminate();
  glfwTerminate();
}

bool AppNative::isOpen() {
  return !glfwWindowShouldClose(window);
}

void AppNative::clearWindowBuff() {
  glClear(GL_COLOR_BUFFER_BIT);
  camera.update();
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

const vec2d& AppNative::mousePos() { return mouse_event.getPos(window); }
void AppNative::setMousePos(const vec2d& pos) { glfwSetCursorPos(window, pos.x(), pos.y()); }


// Camera
void AppNative::camRotate(const vec3f& dist) {
  camera.rotate(dist);
}

void AppNative::camTranslate(const vec3f& quant) {
  camera.translate(quant);
}


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

  TwEventKeyGLFW3(window, key, scancode, action, mods);
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

  TwEventMouseButtonGLFW3(window, button, action, mods);
}

void AppNative::mousePositionCallBack(GLFWwindow* window,
                                      double xpos, double ypos)
{ 
  TwEventMousePosGLFW3(window, xpos, ypos);
}

void AppNative::windowSizeCallback(GLFWwindow* window, const int width, const int height) {
  auto native = (AppNative*)glfwGetWindowUserPointer(window);

  TwEventWindowSizeGLFW3(window, width, height);
  native->camera.setWindowSize(vec2i(width, height));
  glViewport(0, 0, width, height);
}
