
#include <GLFW/glfw3.h>
#include <iostream>


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
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    int key = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (key == GLFW_PRESS) {
      break;
    }

    glfwSetCursorPos(window, 30.0f, 60.0f);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
