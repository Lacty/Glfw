
#pragma once
#include "loader.hpp"
#include "tweakbar.hpp"


class Stage {
private:
  struct Info {
    int current;
    std::vector<float> vertices;
    std::vector<float> colors;

    TwBar* twBar;

    int getCurrentVtx() { return current * 3; }
    int getCurrentCol() { return current * 4; }
    int getNum() { return int(vertices.size()) / 3; }
    bool isUpperLimit() { return int(vertices.size()) == int(getCurrentVtx()); }
    bool isLowerLimit() { return current == 0; }
  } info;

  Loader loader;

  static void TW_CALL goNext(void* _info) {
    Info* info = static_cast<Info*>(_info);
    if (info->isUpperLimit()) return;
    info->current++;
    TwRemoveVar(info->twBar, "vtx");
    TwRemoveVar(info->twBar, "col");
    TwAddVarRW(info->twBar, "vtx", TW_TYPE_DIR3F,
               &info->vertices[info->getCurrentVtx()], "");
    TwAddVarRW(info->twBar, "col", TW_TYPE_QUAT4F,
               &info->colors[info->getCurrentCol()], "");
  }

  static void TW_CALL goBack(void* _info) {
    Info* info = static_cast<Info*>(_info);
    if (info->isLowerLimit()) return;
    info->current--;
    TwRemoveVar(info->twBar, "vtx");
    TwRemoveVar(info->twBar, "col");
    TwAddVarRW(info->twBar, "vtx", TW_TYPE_DIR3F,
               &info->vertices[info->getCurrentVtx()], "");
    TwAddVarRW(info->twBar, "col", TW_TYPE_QUAT4F,
               &info->colors[info->getCurrentCol()], "");
  }

public:
  Stage() :
  loader("assets/stage.json")
  {
    load();
  }
  
  void load() {
    loader.load();
    info.vertices = loader.getVertices();
    info.colors   = loader.getColors();
  }
  
  void registerTw() {
    info.twBar = TwNewBar("stage");
    TwAddButton(info.twBar, "go next", goNext, &info, "");
    TwAddButton(info.twBar, "go back", goBack, &info, "");
    TwAddVarRW(info.twBar, "vtx", TW_TYPE_DIR3F,
               &info.vertices[info.getCurrentVtx()], "");
    TwAddVarRW(info.twBar, "col", TW_TYPE_QUAT4F,
               &info.colors[info.getCurrentCol()], "");
  }

  void draw() {}
};
