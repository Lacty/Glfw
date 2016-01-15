
#pragma once
#include <AntTweakBar/AntTweakBar.h>
#include <GLFW/glfw3.h>


inline void TwEventMouseButtonGLFW3(GLFWwindow* window, int button, int action, int mods)
{ TwEventMouseButtonGLFW(button, action); }
inline void TwEventMousePosGLFW3(GLFWwindow* window, double xpos, double ypos)
{ TwMouseMotion(int(xpos), int(ypos)); }
inline void TwEventMouseWheelGLFW3(GLFWwindow* window, double xoffset, double yoffset)
{ TwMouseWheel(yoffset); }
inline void TwEventKeyGLFW3(GLFWwindow* window, int key, int scancode, int action, int mods)
{ TwEventKeyGLFW(key, action); }
inline void TwEventCharGLFW3(GLFWwindow* window, int codepoint)
{ TwEventCharGLFW(codepoint, GLFW_PRESS); }
inline void TwEventWindowSizeGLFW3(GLFWwindow* window, int width, int height)
{ TwWindowSize(width, height); }


void TwSetEventCallBack(GLFWwindow* window) {
  glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)TwEventMouseButtonGLFW3);
  glfwSetCursorPosCallback  (window, (GLFWcursorposfun)  TwEventMousePosGLFW3);
  glfwSetScrollCallback     (window, (GLFWscrollfun)     TwEventMouseWheelGLFW3);
  glfwSetKeyCallback        (window, (GLFWkeyfun)        TwEventKeyGLFW3);
  glfwSetCharCallback       (window, (GLFWcharfun)       TwEventCharGLFW3);
  glfwSetWindowSizeCallback (window, (GLFWwindowsizefun) TwEventWindowSizeGLFW3);
}
