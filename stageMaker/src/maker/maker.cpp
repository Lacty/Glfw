
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
mode(Mode::EditVtx),
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

  ref_edit.push_back("W: ");

  ref_move.push_back("W: go forward");
  ref_move.push_back("S: go back");
  ref_move.push_back("A: go left");
  ref_move.push_back("D: go right");
  ref_move.push_back("X: go up");
  ref_move.push_back("Z: go down");

  ref_sele.push_back("D: next");
  ref_sele.push_back("A: back");
  ref_sele.push_back("S: save");

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
  Eigen::Vector3f rot(0.0, 0.0, 0.0);

  rot.x() += -mouse.getPos().y() * 0.01f;
  rot.y() +=  mouse.getPos().x() * 0.01f;
  rot.z() = 0.0f;

  camera.moveVector(Eigen::Vector3f(0, 0, 0), rot);

  glfwSetCursorPos(window,
                   getWindowWidth() * 0.5,
                   getWindowHeight() * 0.5);
}

void Maker::transCam() {
  float speed = 0.2f;
  Eigen::Vector3f vec(0, 0, 0);
  if (key.isPress(Keys::W)) { vec.z() += -speed; }
  if (key.isPress(Keys::S)) { vec.z() +=  speed; }
  if (key.isPress(Keys::D)) { vec.x() +=  speed; }
  if (key.isPress(Keys::A)) { vec.x() += -speed; }
  if (key.isPress(Keys::X)) { vec.y() += -speed; }
  if (key.isPress(Keys::Z)) { vec.y() +=  speed; }

  camera.moveVector(vec, Eigen::Vector3f(0, 0, 0));
}

std::string Maker::modeToStr(Mode mode) {
  switch (mode) {
    case EditVtx:
      return "EditVtx";
      break;
    case MoveCam:
      return "MoveCam";
      break;
    case SelectVtx:
      return "SelectVtx";
      break;
  }
}

void Maker::update(GLFWwindow* window) {
  rotateCam(window);
  
  if (key.isPush(Keys::E)) { changeMode(); }

  switch (mode) {
    case EditVtx:
      
      break;
    case MoveCam:
      transCam();
      break;
    case SelectVtx:
      
      break;
  }
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
  float top  = getWindowHeight();
  float size = 20;
  std::string str_mode("MODE: ");
  str_mode += modeToStr(mode);
  font.FaceSize(size);
  font.Render(str_mode.c_str(), str_mode.size(),
              FTPoint(0, top - size, 0));

  int i = 0;
  int offset = size + 15;
  size = 15;
  font.FaceSize(size);
  switch (mode) {
    case EditVtx:
      for (auto it : ref_edit) {
        font.Render(it.c_str(), it.size(),
                    FTPoint(0, top - offset - size * i, 0));
        ++i;
      } break;
    case MoveCam:
      for (auto it : ref_move) {
        font.Render(it.c_str(), it.size(),
                    FTPoint(0, top - offset - size * i, 0));
        ++i;
      } break;
    case SelectVtx:
      for (auto it : ref_sele) {
        font.Render(it.c_str(), it.size(),
                    FTPoint(0, top - offset - size * i, 0));
        ++i;
      } break;
  }
}
