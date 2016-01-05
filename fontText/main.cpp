
#include <GLFW/glfw3.h>
#include <FTGL/ftgl.h>
#include <iostream>
#include <memory>


int main() {
  if (!glfwInit()) return -1;

  GLFWwindow* window;
  window = glfwCreateWindow(640, 480, "fontText", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  // FTGL ---
  FTPixmapFont font("assets/rounded-l-mplus-1c-regular.ttf");
  if (font.Error()) {
    std::cout << "missing .ttf path\n";
    return -1;
  }

  font.FaceSize(100);
  
  FTPoint pos(640 * 0.5f, 480 * 0.5f, 0.0);
  // --- FTGL

  while(!glfwWindowShouldClose(window)) {
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor4f(0.2f, 0.2, 0.6f, 1.0f);
    font.Render("Hello", 5, FTPoint(100.0f, 50.0f));
    font.Render("Ah^~", 4, FTPoint(300.0f, 300.0f));

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
