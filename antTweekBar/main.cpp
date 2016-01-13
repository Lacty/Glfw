
#include <iostream>
#include <AntTweakBar/AntTweakBar.h>
#include <GLFW/glfw3.h>


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
  TwInit(TW_OPENGL, nullptr);
  TwWindowSize(200, 300);
  TwBar* twBar;
  twBar = TwNewBar("tweak bar");

  bool b = false;
  TwAddVarRW(twBar, "tweak bar", TW_TYPE_BOOLCPP, &b, "");

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    TwDraw();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
