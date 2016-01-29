
#pragma once
#include "appNative.hpp"
#include "stage.hpp"
#include "vector.hpp"


class Maker {
private:
  Stage stage;
  
  vec2d clip_mouse_pos;
  
  void updateCamera(AppNative& native);

public:
  Maker() = default;

  void setup();

  void update(AppNative& native);
      
  void draw(AppNative& native);
};
