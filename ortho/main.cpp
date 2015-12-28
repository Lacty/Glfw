
#include <GLFW/glfw3.h>


static float WIDTH = 640;
static float HEIGHT = 480;

void resize(GLFWwindow* window, const int width, const int height) {
  WIDTH = width;
  HEIGHT = height;
  glViewport(0, 0, WIDTH, HEIGHT);
  glLoadIdentity();
  glOrtho(-WIDTH * 0.5f, WIDTH * 0.5f, -HEIGHT * 0.5f, HEIGHT * 0.5f, 0.0f, 1.0f);
}

int main() {
  GLFWwindow* window;

  if (!glfwInit()) {
    return -1;
  }

  window = glfwCreateWindow(640, 480, "changeWindowSize", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetWindowSizeCallback(window, resize);

  glOrtho(-WIDTH * 0.5f, WIDTH * 0.5f, -HEIGHT * 0.5f, HEIGHT * 0.5f, 0.0f, 1.0f);

  float scale = 100.0f;

  while(!glfwWindowShouldClose(window)) {
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat vtx[] = {
      0.0f, 0.433f,
      -0.5f, -0.433f,
      0.5f, -0.433f
    };
    for (auto& it : vtx) {
      it *= scale;
    }

    glVertexPointer(2, GL_FLOAT, 0, vtx);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
