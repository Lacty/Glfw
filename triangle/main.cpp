
#include <iostream>
#include <GLFW/glfw3.h>


int main() {
  GLFWwindow* window;

  if (!glfwInit()) {
    return -1;
  }

  window = glfwCreateWindow(640, 480, "triangle", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  while(!glfwWindowShouldClose(window)) {
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    GLfloat vtx[] = {
      0.0f, 0.433f,
      -0.5f, -0.433f,
      0.5f, -0.433f
    };

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
