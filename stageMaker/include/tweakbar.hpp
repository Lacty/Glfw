
#pragma once
#include <GLFW/glfw3.h>

#define DEBUG_IO 1

#if DEBUG_IO
#include <AntTweakBar/AntTweakBar.h>
#endif


inline void TwEventMouseButtonGLFW3(GLFWwindow* window, int button, int action, int mods) {
#if DEBUG_IO
  TwEventMouseButtonGLFW(button, action);
#endif
}

inline void TwEventMousePosGLFW3(GLFWwindow* window, double xpos, double ypos) {
#if DEBUG_IO
  TwMouseMotion(int(xpos), int(ypos));
#endif
}

inline void TwEventMouseWheelGLFW3(GLFWwindow* window, double xoffset, double yoffset) {
#if DEBUG_IO
  TwMouseWheel(yoffset);
#endif
}

inline void TwEventKeyGLFW3(GLFWwindow* window, int key, int scancode, int action, int mods) {
#if DEBUG_IO
  TwEventKeyGLFW(key, action);
#endif
}

inline void TwEventCharGLFW3(GLFWwindow* window, int codepoint) {
#if DEBUG_IO
  TwEventCharGLFW(codepoint, GLFW_PRESS);
#endif
}

inline void TwEventWindowSizeGLFW3(GLFWwindow* window, int width, int height) {
#if DEBUG_IO
  TwWindowSize(width, height);
#endif
}
