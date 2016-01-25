
#pragma once
#include <GLFW/glfw3.h>

#include "vector.hpp"
#include "color.hpp"
#include "key.hpp"
#include "mouse.hpp"
#include "tweakbar.hpp"
#include "camera.hpp"


class AppNative {
private:
  GLFWwindow* window;
  vec2i window_size;
  
  Key   key_event;
  Mouse mouse_event;

  Camera camera;

public:
  AppNative(int width, int height, const char* title);
  ~AppNative();

  // this class can't copy
  AppNative() = delete;
  AppNative(const AppNative&) = delete;
  AppNative& operator =(const AppNative&) = delete;

  bool isOpen();
  void clearWindowBuff();
  void updateEvent();

  void setClearColor(const Color& color);

  const vec2i& windowSize() const;


  // Key Events
  bool isPushKey(int key);
  bool isPullKey(int key);
  bool isPressKey(int key);

  // Mouse Event
  bool isPushButton(int button);
  bool isPullButton(int button);
  bool isPressButton(int button);

  const vec2d& mousePos() const;
  void setMousePos(const vec2d& pos);

  void camRotate(const vec3f& dist);
  void camTranslate(const vec3f& quant);

  const vec3f& getCamPos() const { return camera.getPos(); }
  const vec3f& getCamRot() const { return camera.getRot(); }

private:
  static void keyCallBack(GLFWwindow* window,
                          const int key,    const int scancode,
                          const int action, const int mods);

  static void mouseButtonCallBack(GLFWwindow* window,
                                  int button, int action, int mods);

  static void mousePositionCallBack(GLFWwindow* window,
                                    double xpos, double ypos);

  static void windowSizeCallback(GLFWwindow* window, const int width, const int height);
};
