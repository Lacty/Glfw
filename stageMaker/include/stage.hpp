
#pragma once
#include "loader.hpp"
#include "tweakbar.hpp"

#include <cassert>


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

  static void TW_CALL addVertex(void* _info) {
    Stage* info = static_cast<Stage*>(_info);
    float X = info->vertices[info->vertices.size() - 3];
    float Y = info->vertices[info->vertices.size() - 2];
    float Z = info->vertices[info->vertices.size() - 1];
    float R = info->colors[info->colors.size() - 4];
    float G = info->colors[info->colors.size() - 3];
    float B = info->colors[info->colors.size() - 2];
    float A = info->colors[info->colors.size() - 1];
    info->vertices.emplace_back(X);
    info->vertices.emplace_back(Y);
    info->vertices.emplace_back(Z);
    info->colors.emplace_back(R);
    info->colors.emplace_back(G);
    info->colors.emplace_back(B);
    info->colors.emplace_back(A);
    info->current_num++;
    updateTwBar(info);
  }

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
  loader("assets/stage.json")
  {
    loader.load();
    vertices = loader.getVertices();
    colors   = loader.getColors();
    
    int dim = 3; // three-dimensional
    assert(vertices.size() % dim == 0);
    current_num = vertices.size() / dim - 1;
  }
 
  void registerTw() {
    twBar = TwNewBar("stage");
    TwAddVarRO(twBar, "current_num", TW_TYPE_INT8, &current_num, "");
    TwAddButton(twBar, "add vertex", addVertex, this, "key=SHIFT+A");
    TwAddButton(twBar, "save",       save,      this, "key=SHIFT+S");
    TwAddButton(twBar, "go next",    goNext,    this, "");
    TwAddButton(twBar, "go back",    goBack,    this, "");
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
