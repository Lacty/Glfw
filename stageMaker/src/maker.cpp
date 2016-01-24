
#include "../include/maker.hpp"


void Maker::updateMouse(AppNative& native) {
  // "Press" mouse right
  // rotate camera
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
  } else
  if (native.isPullButton(GLFW_MOUSE_BUTTON_RIGHT)) {
    isBeganPressLeft = false;
  }
}


void Maker::setup() {
  stage.registerTw();
}

void Maker::update(AppNative& native) {
  updateMouse(native);
}

void Maker::draw() {
  stage.draw();
}
