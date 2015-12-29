
#include <iostream>
#include <GLFW/glfw3.h>


int main() {
  if (!glfwInit()) return -1;

  GLFWwindow* window;
	window = glfwCreateWindow(640, 480, "inputMouse", nullptr, nullptr);
	if (!window) {
	  glfwTerminate();
		return -1;
	}

  glfwMakeContextCurrent(window);

	double mouse_x = 0;
	double mouse_y = 0;

	int event = 0;

  bool isPress   = false;
	bool isRelease = false;

	while(!glfwWindowShouldClose(window)) {
	  glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

    // Mouse Position
		glfwGetCursorPos(window, &mouse_x, &mouse_y);
  	
		// Mouse Press Event
		event = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

		isRelease = event == GLFW_RELEASE ? true : false;

		if (isPress) {
		  std::cout << "press" << std::endl;
		}

		if (isRelease && isPress) {
		  std::cout << "release" << std::endl;
			std::cout << "mouse x = " << mouse_x << std::endl;
			std::cout << "mouse y = " << mouse_y << std::endl;
		}

		// Mouse Press Event
		event = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

    isPress   = event == GLFW_PRESS ?   true : false;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
