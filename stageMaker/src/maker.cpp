
#include "../include/maker.hpp"
#include <Eigen/Geometry>


void Maker::updateCamera(AppNative& native) {
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
  updateCamera(native);
}

void Maker::draw(AppNative& native) {
  stage.draw(/*native.getCamRot()*/vec3f(0, 0, 0));
}
