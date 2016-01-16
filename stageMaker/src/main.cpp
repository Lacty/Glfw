
#include <iostream>
#include <GLFW/glfw3.h>

#include "../include/appNative.hpp"


int main() {
  AppNative native(640, 480, "hoge");
  
  native.setup();
  native.setClearColor(Color::gray());
  while (native.isOpen() && !native.isPushKey(GLFW_KEY_ESCAPE)) {
    native.clearWindowBuff();

    if (native.isPullButton(GLFW_MOUSE_BUTTON_LEFT)) {
      std::cout << "mouse pos\n" << native.getMousePos() << std::endl;
    }

    native.updateEvent();
  }
}
