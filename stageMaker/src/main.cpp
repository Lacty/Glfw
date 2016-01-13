
#include <iostream>
#include <GLFW/glfw3.h>
#include <Eigen/Core>
#include <Eigen/Geometry>

#include "camera/camera.hpp"
#include "window/window.hpp"
#include "maker/maker.hpp"
#include "input/input.hpp"


void resize(GLFWwindow* window,
            const int width,
            const int height)
{
  setWindowSize(width, height);
}

bool isOpen(GLFWwindow* window, const Key& key) {
  return !glfwWindowShouldClose(window) && !key.isPush(Keys::Esc);
}

void initMatrix() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
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


  Camera camera({{ 0.0f, 0.0f,   0.0f },
                 { 0.0f, 0.0f, -10.0f }});

  Mouse  mouse;
  Key    key;
  Maker  maker("assets/stage.json", camera, mouse, key);

  while (isOpen(window, key)) {
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    initMatrix();

    maker.drawUI();

    camera.update();
    mouse.update(window);
    key.update(window);

    maker.update(window);
    maker.draw();
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
