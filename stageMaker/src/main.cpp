
#include <iostream>
#include <GLFW/glfw3.h>

#include "../include/appNative.hpp"


int main() {
  AppNative native(640, 480, "hoge");
  
  native.setClearColor(Color::gray());
  while (native.isOpen()) {
    native.clearWindowBuff();

    native.updateEvent();
  }
}
