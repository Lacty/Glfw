 
#include <iostream>
#include <GLFW/glfw3.h>

#include "../include/appNative.hpp"
#include "../include/maker.hpp"


int main() {
  AppNative native(640, 480, "hoge");
  native.setClearColor(Color::gray());

  Maker maker;
  maker.setup();

  while (native.isOpen() && !native.isPushKey(GLFW_KEY_ESCAPE)) {
    native.clearWindowBuff();
   
    maker.update(native);
    maker.draw();
    TwDraw();

    native.updateEvent();
  }
}
