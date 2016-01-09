
#include <iostream>
#include <GLFW/glfw3.h>
#include <Eigen/Core>
#include <Eigen/Geometry>

#include "camera/camera.hpp"
#include "window/window.hpp"
#include "maker/maker.hpp"
#include "input/input.hpp"
#include "loader/loader.hpp"


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


  Camera camera({{ 0.0f, 0.0f,   0.0f },
                 { 0.0f, 0.0f, -10.0f }});
  camera.setNear(0.5f);
  camera.setFar(50.0f);

  Mouse  mouse;
  Key    key;
  Loader loader("assets/stage.json");
  loader.load();

  std::vector<GLfloat> vtx(loader.getVtx());
  for (auto& it : vtx) {
    std::cout << "vtx = " << it << std::endl;
  }

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    camera.update();
    mouse.update(window);
    key.update(window);

    GLfloat vtx[] = { 0.0f, 0.0f };

    glTranslatef(0.0f, 0.0f, -10.0f);
    glPointSize(50);
    glVertexPointer(2, GL_FLOAT, 0, vtx);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_POINTS, 0, 1);
    glDisableClientState(GL_VERTEX_ARRAY);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
