
#pragma once
#include "appNative.hpp"
#include "stage.hpp"
#include "vector.hpp"


class Maker {
private:
  Stage stage;
  
  bool isBeganPressLeft;
  vec2d clip_mouse_pos;
  
  void updateMouse(AppNative& native);
  void updateCamera(AppNative& native);

public:
  Maker() = default;

  void setup();

  void update(AppNative& native);
      
  void draw(AppNative& native);
};
