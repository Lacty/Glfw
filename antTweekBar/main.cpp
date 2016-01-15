
#include <iostream>
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

int main() {
  if (!glfwInit()) return -1;

  GLFWwindow* window;
  window = glfwCreateWindow(640, 480, "antTweakBar", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  // TweakBar ---
  TwInit(TW_OPENGL, NULL);
  TwWindowSize(640, 480);
  TwBar* twBar;
  twBar = TwNewBar("tweak bar");

  bool b = true;
  TwAddVarRW(twBar, "b", TW_TYPE_BOOLCPP, &b, "");

  float vec[3] = { 1, 2, 3 };
  TwAddVarRW(twBar, "vec", TW_TYPE_DIR3F, &vec, "");

  glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)TwEventMouseButtonGLFW3);
  glfwSetCursorPosCallback  (window, (GLFWcursorposfun)  TwEventMousePosGLFW3);
  glfwSetScrollCallback     (window, (GLFWscrollfun)     TwEventMouseWheelGLFW3);
  glfwSetKeyCallback        (window, (GLFWkeyfun)        TwEventKeyGLFW3);
  glfwSetCharCallback       (window, (GLFWcharfun)       TwEventCharGLFW3);
  glfwSetWindowSizeCallback (window, (GLFWwindowsizefun) TwEventWindowSizeGLFW3);

  while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    TwDraw();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  TwTerminate();
  glfwTerminate();
  return 0;
}
