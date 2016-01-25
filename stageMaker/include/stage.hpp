
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

  static void TW_CALL deleteLast(void* _info) {
    Stage* info = static_cast<Stage*>(_info);
    info->current_num--;
    updateTwBar(info);

    auto vtx_last = info->vertices.end();
    --vtx_last;
    info->vertices.erase(vtx_last--); // Z
    info->vertices.erase(vtx_last--); // Y
    info->vertices.erase(vtx_last--); // X
    
    auto col_last = info->colors.end();
    --col_last;
    info->colors.erase(col_last--); // A
    info->colors.erase(col_last--); // B
    info->colors.erase(col_last--); // G
    info->colors.erase(col_last--); // R
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

  void drawStage() {
    glPushMatrix();

      // TIPS: camera option
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

  void drawHighlight(const vec3f& _rot) {
    glPushMatrix();
      
      // TIPS: camera option
      glTranslatef(0, 0, -10);

      // current editting vtx pos
      glTranslatef(vertices[getCurrentVtxIndex()],     // X
                   vertices[getCurrentVtxIndex() + 1], // Y
                   vertices[getCurrentVtxIndex() + 2]);// Z

      glColor4f(1, 0, 0, 1); // red

      // billboard
      glRotatef(_rot.x(), 1, 0, 0);
      glRotatef(_rot.y(), 0, 1, 0);
      glRotatef(_rot.z(), 0, 0, 1);

      // Rect vertices
      const float vtx[] = {
        -0.04f,  0.04f, 0.0f,
        -0.04f, -0.04f, 0.0f,
         0.04f,  0.04f, 0.0f,
         0.04f, -0.04f, 0.0f
      };

      glVertexPointer(3, GL_FLOAT, 0, vtx);
      glEnableClientState(GL_VERTEX_ARRAY);
      glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
      glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();
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
    TwAddButton(twBar, "add vertex",    addVertex,  this, "key=SHIFT+A");
    TwAddButton(twBar, "delete vertex", deleteLast, this, "key=SHIFT+D");
    TwAddButton(twBar, "save",          save,       this, "key=SHIFT+S");
    TwAddButton(twBar, "go next",       goNext,     this, "");
    TwAddButton(twBar, "go back",       goBack,     this, "");
    TwAddVarRW(twBar, "vtx", TW_TYPE_DIR3F, &vertices[getCurrentVtxIndex()], "");
    TwAddVarRW(twBar, "color", TW_TYPE_COLOR4F, &colors[getCurrentColorIndex()], "");
  }

  void draw(const vec3f& _rot) {
    drawStage();
    drawHighlight(_rot);
  }
};
