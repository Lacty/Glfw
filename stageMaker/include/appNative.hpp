
#pragma once
#include <GLFW/glfw3.h>
#include "vector.hpp"
#include "color.hpp"


class AppNative {
private:
  GLFWwindow* window;
  vec2i window_size;

public:
  AppNative(int width, int height, const char* title);
  ~AppNative();

  // this class can't copy
  AppNative() = delete;
  AppNative(const AppNative&) = delete;
  AppNative& operator =(const AppNative&) = delete;

  void setup();

  bool isOpen();
  void clearWindowBuff();
  void updateEvent();

  void setClearColor(const Color& color);

  const vec2i& windowSize() const;
};
