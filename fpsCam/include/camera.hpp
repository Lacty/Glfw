
#pragma once
#include <GLFW/glfw3.h>
#include "vector.hpp"


class Camera {
private:
  vec3f pos;
  vec3f up;
  vec3f rot;
  vec3f foward;

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
         const vec3f& _foward,
         float _fovy,
         float _near,
         float _far);

  void update();
};
