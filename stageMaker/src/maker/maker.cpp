
#include "maker.hpp"
#include "../camera/camera.hpp"
#include "../input/mouse.hpp"
#include "../input/key.hpp"
#include "../window/window.hpp"

#include <Eigen/Core>


Maker::Maker(const std::string& path,
             Camera& camera,
             Mouse& mouse,
             Key& key) :
camera(camera),
mouse(mouse),
key(key),
loader(path)
{
  std::cout << "create Maker" << std::endl;

  loader.load();

  stage_vertex  = loader.getVtx();
  editing_index = stage_vertex.size();
}

void Maker::changeVtx(int d) {
  editing_index += 3 * d;
}

void Maker::save() {
  loader.save(stage_vertex);
}

void Maker::changeMode() {
  // EditVtx -> MoveCam -> SelectVtx
  mode = mode == EditVtx
           ? MoveCam
           : mode == MoveCam
             ? SelectVtx
             : EditVtx;
}

void Maker::rotateCam(GLFWwindow* window) {
  Eigen::Vector3f rot;
  
  glfwSetCursorPos(window,
                   getWindowWidth() * 0.5,
                   getWindowHeight() * 0.5);
}

void Maker::transCam() {
  float speed = 0.2f;
  Eigen::Vector3f vec;
  if (key.isPress(Keys::W)) { vec.z() +=  speed; }
  if (key.isPress(Keys::S)) { vec.z() += -speed; }
  if (key.isPress(Keys::D)) { vec.x() +=  speed; }
  if (key.isPress(Keys::A)) { vec.x() += -speed; }
  if (key.isPress(Keys::X)) { vec.y() +=  speed; }
  if (key.isPress(Keys::Z)) { vec.y() += -speed; }

  camera.moveVector(vec, Eigen::Vector3f(0, 0, 0));
}

void Maker::drawUI() {}

void Maker::update(GLFWwindow* window) {
  rotateCam(window);
}

void Maker::draw() {}
