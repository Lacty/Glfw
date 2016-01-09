
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
  Maker  maker("assets/stage.json", camera, mouse, key);

  float angle = 0.0f;
  float rotate = 0.0f;

  while (isOpen(window, key)) {
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    camera.update();
    mouse.update(window);
    key.update(window);

    if (key.isPress(Keys::A)) {
      angle += 0.1f;
    } else if (key.isPress(Keys::D)) {
      angle -= 0.1f;
    }
    if (key.isPress(Keys::Z)) {
      rotate += 0.1f;
    } else if (key.isPress(Keys::X)) {
      rotate -= 0.1f;
    }

    std::cout << "camera pos\n" << camera.getPos() << std::endl;
    std::cout << "camera rot\n" << camera.getRot() << std::endl;

    camera.setPos(Eigen::Vector3f(angle, 0.0f, 0.0f));
    camera.setTargetPos(Eigen::Vector3f(angle, 0.0f, -10.0f));
    camera.setRot(Eigen::Vector3f(0.0f, rotate, 0.0f));

    GLdouble modelMatrix[4*4];
    glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);

    GLfloat vtx[] = { 0.0f, 0.0f, -10.0f };

    glPointSize(50);
    glVertexPointer(3, GL_FLOAT, 0, vtx);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_POINTS, 0, 1);
    glDisableClientState(GL_VERTEX_ARRAY);

    glMultMatrixd(modelMatrix);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
