
#include <GLFW/glfw3.h>


int main() {
  GLFWwindow* window;

  if (!glfwInit()) {
    return -1;
  }

  window = glfwCreateWindow(640, 480, "emptyWindow", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  while(!glfwWindowShouldClose(window)) {
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
