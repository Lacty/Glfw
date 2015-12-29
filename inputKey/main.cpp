
#include <iostream>
#include <GLFW/glfw3.h>


int main() {
  if (!glfwInit()) return -1;

  GLFWwindow* window;
	window = glfwCreateWindow(640, 480, "input Key", nullptr, nullptr);
	if (!window) {
	  glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	while(!glfwWindowShouldClose(window)) {
	  glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

    int event = glfwGetKey(window, GLFW_KEY_W);
    if (event == GLFW_PRESS) {
		  std::cout << "press w" << std::endl;
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
