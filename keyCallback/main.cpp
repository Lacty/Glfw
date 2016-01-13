
#include <iostream>
#include <GLFW/glfw3.h>
#include <set>


class Key {
private:
  Key() = default;

  std::set<int> push;
  std::set<int> pull;
  std::set<int> press;

  static Key& get() {
    static Key key;
    return key;
  }

public:
  static void clear() {
    get().push.clear();
    get().pull.clear();
  }

  static void setKeyPush(int key) {
    get().push.emplace(key);
  }

  static void setKeyPull(int key) {
    get().pull.emplace(key);
  }

  static void setKeyPress(int key) {
    get().press.emplace(key);
  }

  static void popKeyPress(int key) {
    get().press.erase(get().press.find(key));
  }

  static bool isPush(int key) {
    if (get().push.find(key) == get().push.end()) return false;
    get().push.erase(get().push.find(key));
    return true;
  }

  static bool isPull(int key) {
    if (get().pull.find(key) == get().pull.end()) return false;
    get().pull.erase(get().pull.find(key));
    return true;
  }

  static bool isPress(int key) {
    if (get().press.find(key) == get().press.end()) return false;
    return true;
  }
};

void keyCallback(GLFWwindow* window,
                 int key,
                 int scancode,
                 int action,
                 int mods)
{
  if (action == GLFW_PRESS) {
    Key::setKeyPush(key);
    Key::setKeyPress(key);
  }
  if (action == GLFW_RELEASE) {
    Key::setKeyPull(key);
    Key::popKeyPress(key);
  }
}

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
  glfwSetKeyCallback(window, keyCallback);

  while(!glfwWindowShouldClose(window)
     && !glfwGetKey(window, GLFW_KEY_ESCAPE))
  {
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
 
    Key::clear();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
