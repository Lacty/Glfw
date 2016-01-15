
#include <iostream>
#include <AntTweakBar/AntTweakBar.h>
#include <GLFW/glfw3.h>


inline void TwEventWindowSizeGLFW3(GLFWwindow* window, int width, int height)
{TwWindowSize(width, height);}

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

  glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)TwEventMouseButtonGLFW);
  glfwSetCursorPosCallback(window, (GLFWcursorposfun)TwMouseMotion);
  glfwSetKeyCallback(window, (GLFWkeyfun)TwEventKeyGLFW);
  glfwSetCharCallback(window, (GLFWcharfun)TwEventCharGLFW);
  glfwSetWindowSizeCallback(window, TwEventWindowSizeGLFW3);

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
