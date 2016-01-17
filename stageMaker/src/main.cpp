
#include <iostream>
#include <GLFW/glfw3.h>

#include "../include/appNative.hpp"


int main() {
  AppNative native(640, 480, "hoge");
  
  native.setup();
  native.setClearColor(Color::gray());

  vec3f pos(10, 20, 30);

  auto* twBar = TwNewBar("test bar");
  TwAddVarRW(twBar, "pos", TW_TYPE_DIR3F, &pos, "");

  while (native.isOpen() && !native.isPushKey(GLFW_KEY_ESCAPE)) {
    native.clearWindowBuff();
    
    TwDraw();

    native.updateEvent();
  }
}
