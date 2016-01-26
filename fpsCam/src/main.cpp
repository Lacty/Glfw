
#include <iostream>
#include <GLFW/glfw3.h>
#include "../include/vector.hpp"
#include "../include/camera.hpp"


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
  vec3f foward(0, 0, -1);
  float fovy = 35.0f;
  float near = 0.5f;
  float far  = 50.0f;

  Camera cam(width, height,
             pos, up, rot, foward,
             fovy, near, far);

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
    
    // ROTATE --
    glRotatef(-rot.x(), 0, 1, 0); // YOKO
    glRotatef(-rot.y(), 1, 0, 0); // TATE

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
      rot = vec3f(0, 0, 0);
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
          glRotatef(rot.x(), 0, 1, 0);
          glRotatef(rot.y(), 1, 0, 0);

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
    rot.x() += (width * 0.5  - mouse.x()) * 0.1;
    rot.y() += (height * 0.5 - mouse.y()) * 0.1;
    glfwSetCursorPos(window, width * 0.5, height * 0.5);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
}
