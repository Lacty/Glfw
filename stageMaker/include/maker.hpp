
#pragma once
#include "appNative.hpp"
#include "stage.hpp"
#include "vector.hpp"


class Maker {
private:
  Stage stage;
  
  bool isBeganPressLeft;
  vec2d clip_mouse_pos;
  

public:
  Maker() {};

  void setup() {
    stage.registerTw();
  }

  void update(AppNative& native) {
    if (native.isPressButton(GLFW_MOUSE_BUTTON_RIGHT)) {
      if (!isBeganPressLeft) {
        clip_mouse_pos = native.mousePos();
        isBeganPressLeft = true;
      }
      vec3f rotate(0.0f, 0.0f, 0.0f);

      rotate.x() = native.mousePos().y() - clip_mouse_pos.y();
      rotate.y() = native.mousePos().x() - clip_mouse_pos.x();
      rotate.z() = 0.0f;

      rotate *= 0.004f;
      native.camRotate(rotate);
      native.setMousePos(clip_mouse_pos);
    }
    if (native.isPullButton(GLFW_MOUSE_BUTTON_LEFT)) {
      isBeganPressLeft = false;
    }
  }
  
  void draw() {
    stage.draw();
  }
};
