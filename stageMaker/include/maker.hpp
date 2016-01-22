
#pragma once
#include "appNative.hpp"
#include "stage.hpp"


class Maker {
private:
  Stage stage;

public:
  Maker() {};

  void setup() {
    stage.registerTw();
  }

  void update(const AppNative& native) {}

  void draw() {
    stage.draw();
  }
};
