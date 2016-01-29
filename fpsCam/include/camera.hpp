
#pragma once
#include <GLFW/glfw3.h>
#include "vector.hpp"


class Camera {
private:
  vec3f pos;
  vec3f up;
  vec3f rot;
  vec3f target;

  float fovy;
  float aspect;
  float near;
  float far;

  void perspView();
  void lookAt();

  void perspTrans();

public:
  Camera() = default;
  Camera(int _width, int _height,
         const vec3f& _pos,
         const vec3f& _up,
         const vec3f& _rot,
         const vec3f& _target,
         float _fovy,
         float _near,
         float _far);

  void setTarget(const vec3f& _target) {
    target = _target;
  }

  void setPos(const vec3f& _pos) {
    pos = _pos;
  }

  void setUp(const vec3f& _up) {
    up = _up;
  }

  void update();
};
