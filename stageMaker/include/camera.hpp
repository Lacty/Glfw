
#pragma once
#include "vector.hpp"
#include "tweakbar.hpp"


class Camera {
private:
  vec2i window_size;

  vec3f pos;
  vec3f up;
  vec3f target;
  vec3f forward;
  vec3f rot;

  float fovy;
  float near;
  float far;

  float translateSpeedScale;
  float rotateSpeedScale;

  void perspView();

  void lookAt();
  void perspTrans();

  void evaluateRotate();

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

  void setPos   (const vec3f& pos)    { this->pos    = pos; }
  void setUp    (const vec3f& up)     { this->up     = up; }
  void setTarget(const vec3f& target) { this->target = target; }

  void setFovy(float fovy) { this->fovy = fovy; }
  void setNear(float near) { this->near = near; }
  void setFar (float far)  { this->far  = far; }

  const vec3f& getPos()    const { return pos; }
  const vec3f& getUp()     const { return up; }
  const vec3f& getTarget() const { return target; }
  const vec3f& getRot()    const { return rot; }

  const float getFovy() const { return fovy; }
  const float getNear() const { return near; }
  const float getFar()  const { return far; }
};
