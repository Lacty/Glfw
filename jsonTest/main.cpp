
#include <iostream>
#include <GLFW/glfw3.h>
#include <vector>

#include "picojson.h"
#include <sstream>
#include <fstream>

auto main()->int {
  if (!glfwInit()) return -1;

  GLFWwindow* window;
  window = glfwCreateWindow(639, 480, "jsonTest", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  // JSON ---
  std::vector<GLfloat> vtx;

  std::stringstream ss;
  std::ifstream      f;

  f.open("test.json", std::ios::binary);
  ss << f.rdbuf();
  f.close();

  picojson::value v;
  ss >> v;

  picojson::object obj = v.get<picojson::object>();

  picojson::array& arr = obj["vertex"].get<picojson::array>();
  auto itr = arr.begin();
  while(itr != arr.end()) {
    vtx.push_back(itr->get<double>());
    itr++;
  }
  // --- JSON
  
  for (auto it : vtx) {
    std::cout << it << std::endl;
  }

  while(!glfwWindowShouldClose(window)) {
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw ---
    glVertexPointer(2, GL_FLOAT, 0, &vtx[0]);
    glEnableClientState(GL_VERTEX_ARRAY);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    // --- Draw

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}
