
#include <iostream>
#include <GLFW/glfw3.h>

#include "../include/appNative.hpp"


int main() {
  AppNative native(640, 480, "hoge");
  
  native.setClearColor(Color::gray());
  while (native.isOpen() && !native.isPushKey(GLFW_KEY_ESCAPE)) {
    native.clearWindowBuff();
    
    if (native.isPressKey(GLFW_KEY_W)) {
      std::cout << "press W" << std::endl;
    }

    native.updateEvent();
  }
}
