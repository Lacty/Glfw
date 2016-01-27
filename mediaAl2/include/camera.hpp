
#pragma once
#include "vector.hpp"
#include "tweakbar.hpp"


class Camera {
private:
  vec2i window_size;

  vec3f pos;
  vec3f rot;
  vec3f up;
  vec3f target_pos;
  vec3f target_dist;

  float fovy;
  float near;
  float far;

  mat4f perspView();

  void lookAt();
  void perspTrans();

  TwBar* twBar;

public:
  Camera() = default;
  Camera(const vec3f& pos, const vec3f& target_pos);

  void registerTw();

  void update();

  void translate(const vec3f& dist);
  void rotate(const vec3f& quant);

  float getAspect() { return window_size.x() / float(window_size.y()); }
  void setWindowSize(const vec2i& size) { window_size = size; }

  void setPos      (const vec3f& pos)    { this->pos        = pos; }
  void setRot      (const vec3f& rot)    { this->rot        = rot; }
  void setUp       (const vec3f& up)     { this->up         = up; }
  void setTargetPos(const vec3f& target) { this->target_pos = target; }

  void setFovy(float fovy) { this->fovy = fovy; }
  void setNear(float near) { this->near = near; }
  void setFar (float far)  { this->far  = far; }

  const vec3f& getPos()       const { return pos; }
  const vec3f& getRot()       const { return rot; }
  const vec3f& getUp()        const { return up; }
  const vec3f& getTargetPos() const { return target_pos; }

  const float getFovy() const { return fovy; }
  const float getNear() const { return near; }
  const float getFar()  const { return far; }
};
