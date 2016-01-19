
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

    float vtx[] = {
      0.0f, 0.433f, 0.0f,
      -0.5f, -0.433f, 0.0f,
      0.5f, -0.433f, 0.0f
    };
   
    glTranslatef(0.0f, 0.0f, -10.0f);
    glVertexPointer(3, GL_FLOAT, 0, vtx);
    glEnableClientState(GL_VERTEX_ARRAY);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);

    native.updateEvent();
  }
}
