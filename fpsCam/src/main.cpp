
#include <iostream>
#include <GLFW/glfw3.h>
#include <Eigen/Geometry>
#include "../include/vector.hpp"
#include "../include/camera.hpp"


float toRadians(float deg) {
  return (deg * M_PI) / 180.0f;
}

float toDegree(float rad) {
  return (rad * 180) / M_PI;
}

int main() {
  if (!glfwInit()) return -1;

  int width  = 640;
  int height = 480;

  GLFWwindow* window;
  window = glfwCreateWindow(width, height, "fpsCam", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  
  vec3f pos(0, 0, 0);
  vec3f up(0, 1, 0);
  vec3f rot(0, 0, 0);
  vec3f forward(0, 0, -1);
  float fovy = 35.0f;
  float near = 0.5f;
  float far  = 50.0f;

  Camera cam(width, height,
             pos, up, rot, forward,
             fovy, near, far);

  vec3f billRot(0, 0, 0);

  vec2d mouse(width * 0.5, height * 0.5);
  glfwSetCursorPos(window, mouse.x(), mouse.y());

  while (!glfwWindowShouldClose(window)                      // close
     && (GLFW_PRESS != glfwGetKey(window, GLFW_KEY_ESCAPE))) // x, esc
  {
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    cam.update();

    const static GLfloat vtx[] = {
      -0.1,  0.1, 0.0,
      -0.1, -0.1, 0.0,
       0.1,  0.1, 0.0,
       0.1, -0.1, 0.0
    };
    
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
      billRot = vec3f(0, 0, 0);
      forward = vec3f(0, 0, -1);
    }

    glVertexPointer(3, GL_FLOAT, 0, vtx);
    glEnableClientState(GL_VERTEX_ARRAY);

    for (int i = -10; i < 11; i++) {
      for (int k = -10; k < 11; k++) {
        for (int h = -10; h < 11; h++) {
          if (((h >= -9 && h <= 9)
            && (k >= -9 && k <= 9)
            && (i >= -9 && i <= 9))) continue;
          glPushMatrix();

          glTranslatef(i, k, h);
          glRotatef(billRot.y(), 1, 0, 0);
          glRotatef(billRot.x(), 0, 1, 0);

          glColor4f(1, 1, 1, 1);
          if (i == 0) glColor4f(1, 0, 0, 1);
          if (k == 0) glColor4f(0, 1, 0, 1);
          if (h == 0) glColor4f(0, 0, 1, 1);
          glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

          glPopMatrix();
        }
      }
    }

    glDisableClientState(GL_VERTEX_ARRAY);


    // MOUSE ---
    glfwGetCursorPos(window, &mouse[0], &mouse[1]);
    rot.x() = (width * 0.5  - mouse.x()) * 0.1;
    rot.y() = (height * 0.5 - mouse.y()) * 0.1;
    billRot.x() += rot.x();
    billRot.y() += rot.y();
    
    Eigen::Quaternionf quat;
    quat = Eigen::AngleAxisf(toRadians(rot.x()), up);
    forward = quat * forward;
    quat = Eigen::AngleAxisf(toRadians(rot.y()), forward.cross(up));
    forward = quat * forward;

    cam.setForward(forward);

    glfwSetCursorPos(window, width * 0.5, height * 0.5);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
}
