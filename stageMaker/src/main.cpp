
#include <iostream>
#include <GLFW/glfw3.h>
#include <Eigen/Core>
#include <Eigen/Geometry>

#include "camera/camera.hpp"
#include "window/window.hpp"
#include "maker/maker.hpp"


void resize(GLFWwindow* window,
            const int width,
            const int height)
{
  setWindowSize(width, height);
}

auto main()->int {
  if (!glfwInit()) return -1;

  setWindowSize(640, 480);

  GLFWwindow* window;
  window = glfwCreateWindow(getWindowWidth(), getWindowHeight(),
                            "stageMaker", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetWindowSizeCallback(window, resize);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
