#pragma once
#include <GLFW/glfw3.h>
#include <FTGL/ftgl.h>
#include <vector>
#include <string>
#include <unordered_map>
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

  std::vector<std::string> ref_edit;
  std::vector<std::string> ref_move;
  std::vector<std::string> ref_sele;

  std::vector<GLfloat> stage_vertex;
  int                  editing_index;

  FTPixmapFont font;

  void changeVtx(int d);
  void save();
  void changeMode();

  void rotateCam(GLFWwindow* window);
  void transCam();

  std::string modeToStr(Mode mode);

public:
  Maker() = default;
  Maker(const std::string& path,
        Camera& camera,
        Mouse& mouse,
        Key& key);
  
  void update(GLFWwindow* window);
  void draw();
  void drawUI();
};
