
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
loader(path),
font("assets/rounded-l-mplus-1c-regular.ttf")
{
  std::cout << "create Maker" << std::endl;

  loader.load();

  stage_vertex  = loader.getVtx();
  editing_index = stage_vertex.size();

  if (font.Error()) {
    std::cout << "missing .ttf load\n";
    exit(1);
  }
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
  Eigen::Vector3d center(getWindowWidth() * 0.5,
                         getWindowHeight() * 0.5,
                         0.0);
  Eigen::Vector3f rot(0.0, 0.0, 0.0);
  
  std::cout << mouse.getPos() << std::endl;

  rot.x() += -mouse.getPos().y() * 0.01f;
  rot.y() += mouse.getPos().x() * 0.01f;
  rot.z() = 0.0f;

  camera.moveVector(Eigen::Vector3f(0, 0, 0), rot);

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

void Maker::update(GLFWwindow* window) {
  rotateCam(window);
}

void Maker::draw() {
  GLfloat vtx[] = {
      0.0f, 0.433f,
      -0.5f, -0.433f,
      0.5f, -0.433f
  };

  glTranslatef(0.0f, 0.0f, -10.0f);
  glVertexPointer(2, GL_FLOAT, 0, vtx);
  glEnableClientState(GL_VERTEX_ARRAY);

  glDrawArrays(GL_TRIANGLES, 0, 3);

  glDisableClientState(GL_VERTEX_ARRAY);
}

void Maker::drawUI() {
  FTPoint pos(0, 0, 0);
  font.FaceSize(100);
  font.Render("UI", 2, pos);
}
