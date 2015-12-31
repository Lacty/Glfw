
#include <iostream>
#include <GLFW/glfw3.h>
#include <Eigen/Core>
#include <Eigen/Geometry>


static int WIDTH = 640;
static int HEIGHT = 480;

void resize(GLFWwindow* window,
            const int width,
            const int height)
{
  WIDTH = width;
  HEIGHT = height;
}

float toRadians(float deg) {
  return (deg * M_PI) / 180.0f;
}

Eigen::Matrix4f perspView(float fovy,
                          float aspect,
                          float near,
                          float far)
{
  float f = 1 / std::tan(toRadians(fovy) * 0.5f);
  float g = -((far +  near) / (far - near));
  float h = -((2 * far * near) / (far - near));
  float i = f / aspect;

  Eigen::Matrix4f m;
  m <<    i,  0.0f,  0.0f,  0.0f,
       0.0f,     f,  0.0f,  0.0f,
       0.0f,  0.0f,     g,     h,
       0.0f,  0.0f,    -1,  0.0f;

  return m;
}

void perspTrans() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  float aspect = WIDTH / float(HEIGHT);
  Eigen::Matrix4f m = perspView(36, aspect, 0.5f, 50.0f);
  glMultMatrixf(m.data());

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
  float scale = 5.0f;

  while(!glfwWindowShouldClose(window)) {
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    perspTrans();

    GLfloat vtx[] = {
      0.0f, 0.433f, 0.0f,
      -0.5f, -0.433f, 0.0f,
      0.5f, -0.433f, 0.0f
    };

    glTranslatef(0.0f, 0.0f, -10.0f);
    glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
    glScalef(scale, scale, scale);

    angle += 1.0f;
    glRotatef(angle, 0.5f, 0.5f, 0.0f);

    glColor4f(0.4f, 0.3f, 0.6f, 1.0f);
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
