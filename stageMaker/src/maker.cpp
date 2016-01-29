
#include "../include/maker.hpp"
#include <Eigen/Geometry>


void Maker::updateMouse(AppNative& native) {
  // "Press" mouse right
  // rotate camera
  if (native.isPressButton(GLFW_MOUSE_BUTTON_RIGHT)) {
    if (!isBeganPressLeft) {
      clip_mouse_pos = native.mousePos();
      std::cout << "press\n" << native.mousePos() << std::endl;;
      isBeganPressLeft = true;
    }
    vec3f angle(0.0f, 0.0f, 0.0f);

    angle.x() = clip_mouse_pos.x() - native.mousePos().x();
    angle.y() = clip_mouse_pos.y() - native.mousePos().y();
    angle.z() = 0;

    native.camRotate(angle);
    native.setMousePos(clip_mouse_pos);
  } else
  if (native.isPullButton(GLFW_MOUSE_BUTTON_RIGHT)) {
    isBeganPressLeft = false;
  }
}

void Maker::updateCamera(AppNative& native) {
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
}


void Maker::setup() {
  stage.registerTw();
}

void Maker::update(AppNative& native) {
  updateMouse(native);
  updateCamera(native);
}

void Maker::draw(AppNative& native) {
  stage.draw(native.getCamRot());
}
