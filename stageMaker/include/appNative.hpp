
#pragma once
#include <GLFW/glfw3.h>

#include "vector.hpp"
#include "color.hpp"
#include "key.hpp"


class AppNative {
private:
  GLFWwindow* window;
  vec2i window_size;
  
  Key key_event;

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


  // Key Events
  bool isPushKey(int key);
  bool isPullKey(int key);
  bool isPressKey(int key);


private:
  // call by glfw
  static void keyCallBack(GLFWwindow* window,
                          const int key,    const int scancode,
                          const int action, const int mods);
};
