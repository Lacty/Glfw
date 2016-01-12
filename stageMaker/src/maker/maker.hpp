
#pragma once
#include <string>
#include <GLFW/glfw3.h>
#include <vector>
#include "../loader/loader.hpp"


class Camera;
class Mouse;
class Key;

class Maker {
private:
  enum Mode {
    EditVtx,
    MoveCam,
    SelectVtx
  } mode;

  Camera& camera;
  Mouse&  mouse;
  Key&    key;
  Loader  loader;

  std::vector<GLfloat> stage_vertex;
  int                  editing_index;

  void changeVtx(int d);
  void save();
  void changeMode();

  void rotateCam(GLFWwindow* window);
  void transCam();

  void drawUI();

public:
  Maker() = default;
  Maker(const std::string& path,
        Camera& camera,
        Mouse& mouse,
        Key& key);
  
  void update(GLFWwindow* window);
  void draw();
};
