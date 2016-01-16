
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
  
  glfwMakeContextCurrent(window);
}

AppNative::~AppNative() {
  glfwTerminate();
}

void AppNative::setup() {}

bool AppNative::isOpen() {
  return !glfwWindowShouldClose(window);
}

void AppNative::clearWindowBuff() {
  glClear(GL_COLOR_BUFFER_BIT);
}

void AppNative::updateEvent() {
  glfwSwapBuffers(window);
  glfwPollEvents();
}


void AppNative::setClearColor(const Color& color) {
  glClearColor(color.r, color.g, color.b, color.a);
}

const vec2i& AppNative::windowSize() const {
  return window_size;
}
