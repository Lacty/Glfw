
#include <iostream>
#include <cmath>
#include <GLFW/glfw3.h>


static int WIDTH = 640;
static int HEIGHT = 480;

void resize(GLFWwindow* window,
            const int width,
            const int height)
{
  WIDTH = width;
  HEIGHT = height;
}

void perspTransformation() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
  glFrustum( -1,   1, // left   right
              1,  -1, // buttom top
            0.5, 5.0);// near   far

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

auto main()->int {
  if (!glfwInit()) return -1;

  GLFWwindow* window;
  window = glfwCreateWindow(640, 480, "camera", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetWindowSizeCallback(window, resize);

  float angle = 0.0f;

  while(!glfwWindowShouldClose(window)) {
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    perspTransformation();

    GLfloat vtx[] = {
      0.0f, 0.433f, 0.0f,
      -0.5f, -0.433f, 0.0f,
      0.5f, -0.433f, 0.0f
    };

    // viewable position z(-0.5 ~ -5.0)
    glTranslatef(0.0f, 0.0f, -1.5f); // to viewable
    glRotatef(180, 0.0f, 0.0f, 1.0f);// to revers
    glScalef(2.0f, 2.0f, 1.0f);

    angle += 2.0f;
    glRotatef(angle, 0.5f, 0.25f, 0.25f);

    glColor4f(1.0f, 0.4f, 0.0f, 1.0f);
    glVertexPointer(3, GL_FLOAT, 0, vtx);

    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
