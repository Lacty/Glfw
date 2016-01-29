
#include "../include/maker.hpp"
#include <Eigen/Geometry>


void Maker::updateCamera(AppNative& native) {
  // KEY ---
  if (native.isPressKey(GLFW_KEY_W)) {
    native.camTranslate(vec3f(0, 0, 1));
  }
  if (native.isPressKey(GLFW_KEY_S)) {
    native.camTranslate(vec3f(0, 0, -1));
  }
  if (native.isPressKey(GLFW_KEY_D)) {
    native.camTranslate(vec3f(1, 0, 0));
  }
  if (native.isPressKey(GLFW_KEY_A)) {
    native.camTranslate(vec3f(-1, 0, 0));
  }

  // MOUSE ---
  if (native.isPushButton(GLFW_MOUSE_BUTTON_RIGHT)) {
    clip_mouse_pos = native.mousePos();
  }

  if (!native.isPressButton(GLFW_MOUSE_BUTTON_RIGHT)) return;
  vec2d angle = clip_mouse_pos - native.mousePos();
  native.camRotate(vec3f(angle.x(), angle.y(), 0));
  native.setMousePos(clip_mouse_pos);
}


void Maker::setup() {
  stage.registerTw();
}

void Maker::update(AppNative& native) {
  updateCamera(native);
}

void Maker::draw(AppNative& native) {
  stage.draw(native.getCamRot());
}
