
#pragma once
#include "loader.hpp"
#include "tweakbar.hpp"


class Stage {
private:
  Loader loader;

  int current_num;
  int getCurrentVtxIndex() { return current_num * 3; }
  int getCurrentColorIndex() { return current_num * 4; }
 
  int getVtxIndex() { return int(vertices.size()) / 3; }

  bool isUpperLimit() { return int(vertices.size()) == current_num * 3 + 3; }
  bool isLowerLimit() { return current_num == 0; }

  std::vector<float> vertices;
  std::vector<float> colors;

  TwBar* twBar;

  static void updateTwBar(Stage* _info) {
    TwRemoveVar(_info->twBar, "vtx");
    TwRemoveVar(_info->twBar, "color");
    TwAddVarRW(_info->twBar, "vtx", TW_TYPE_DIR3F,
               &_info->vertices[_info->getCurrentVtxIndex()], "");
    TwAddVarRW(_info->twBar, "color", TW_TYPE_COLOR4F,
               &_info->colors[_info->getCurrentColorIndex()], "");
  }

  static void TW_CALL save(void* _info) {
    Stage* info = static_cast<Stage*>(_info);
    info->loader.save(info->vertices, info->colors);
  }

  static void TW_CALL goNext(void* _info) {
    Stage* info = static_cast<Stage*>(_info);
    if (info->isUpperLimit()) return;
    info->current_num++;
    updateTwBar(info);
  }

  static void TW_CALL goBack(void* _info) {
    Stage* info = static_cast<Stage*>(_info);
    if (info->isLowerLimit()) return;
    info->current_num--;
    updateTwBar(info);
  }

public:
  Stage() :
  loader("assets/stage.json"),
  current_num(0) {
    loader.load();
    vertices = loader.getVertices();
    colors   = loader.getColors();
  }
 
  void registerTw() {
    twBar = TwNewBar("stage");
    TwAddVarRO(twBar, "current_num", TW_TYPE_INT8, &current_num, "");
    TwAddButton(twBar, "save", save, this, "");
    TwAddButton(twBar, "go next", goNext, this, "");
    TwAddButton(twBar, "go back", goBack, this, "");
    TwAddVarRW(twBar, "vtx", TW_TYPE_DIR3F, &vertices[getCurrentVtxIndex()], "");
    TwAddVarRW(twBar, "color", TW_TYPE_COLOR4F, &colors[getCurrentColorIndex()], "");
  }

  void draw() {
    glPushMatrix();
      glTranslatef(0, 0, -10);
      glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
      glColorPointer(4, GL_FLOAT, 0, &colors[0]);

      glEnableClientState(GL_VERTEX_ARRAY);
      glEnableClientState(GL_COLOR_ARRAY);

      glDrawArrays(GL_TRIANGLE_STRIP, 0, getVtxIndex());

      glDisableClientState(GL_COLOR_ARRAY);
      glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
  }
};
