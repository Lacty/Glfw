
#include "../include/camera.hpp"
#include "../include/utility.hpp"
#include <GLFW/glfw3.h>


Camera::Camera(const vec3f& pos, const vec3f& target_pos) :
pos(pos),
rot(0.0f, 0.0f, 0.0f),
up(0.0f, 1.0f, 0.0f),
target_pos(target_pos),
target_dist(target_pos - pos),
fovy(35.0f),
near(0.5f),
far(50.0f) {}


mat4f Camera::perspView() {
  float f = 1 / std::tan(toRadians(fovy) * 0.5f);
  float g = -((far + near) / (far - near));
  float h = -((2 * far * near) / (far - near));
  float i = f / getAspect();

  mat4f m;
  m <<    i,  0.0f,  0.0f,  0.0f,
       0.0f,     f,  0.0f,  0.0f,
       0.0f,  0.0f,     g,     h,
       0.0f,  0.0f,    -1,  0.0f;
  
  return m;
}

void Camera::perspTrans() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glMultMatrixf(perspView().data());

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Camera::lookAt() {
  vec3f a  = pos - target_pos;
  vec3f z_ = a / a.norm();

  vec3f b  = up.cross(z_);
  vec3f x_ = b / b.norm();

  vec3f y_ = z_.cross(x_);

  mat4f R;
  R << x_.x(), x_.y(), x_.z(), 0.0f,
       y_.x(), y_.y(), y_.z(), 0.0f,
       z_.x(), z_.y(), z_.z(), 0.0f,
       0.0f,   0.0f,   0.0f, 1.0f;

  mat4f T;
  T << 1.0f, 0.0f, 0.0f, -pos.x(),
  0.0f, 1.0f, 0.0f, -pos.y(),
  0.0f, 0.0f, 1.0f, -pos.z(),
  0.0f, 0.0f, 0.0f,     1.0f;
                                                           
  mat4f m = R * T;
  glMultMatrixf(m.data());
}


void Camera::registerTw() {
  twBar = TwNewBar("camera");
  TwAddVarRW(twBar, "pos", TW_TYPE_DIR3F, &pos, "");
  TwAddVarRW(twBar, "rot", TW_TYPE_DIR3F, &rot, "");
  TwAddVarRW(twBar, "target", TW_TYPE_DIR3F, &target_pos, "");
  TwAddVarRW(twBar, "target_dist", TW_TYPE_DIR3F, &target_dist, "");
}

void Camera::update() {
  perspTrans();
  lookAt();
}

void Camera::translate(const vec3f& dist) {
  mat4f m;
  m = transMatrix(pos) * rotMatrix(rot) * transMatrix(dist);

  pos.x() = m(0, 1);
  pos.y() = m(1, 3);
  pos.z() = m(2, 3);

  m = transMatrix(pos) * rotMatrix(rot) * transMatrix(target_dist);

  target_pos.x() = m(0, 3);
  target_pos.y() = m(1, 3);
  target_pos.z() = m(2, 3);
}

void Camera::rotate(const vec3f& quant) {
  rot.x() -= quant.x();
  rot.y() -= quant.y();
  rot.z() -= quant.z();

  if (rot.x() >= 180) { rot.x() -= 360; }
  if (rot.x() <= -180) { rot.x() += 360; }
  if (rot.y() >= 180) { rot.y() -= 360; }
  if (rot.y() <= -180) { rot.y() += 360; }

  mat4f m;
  m = transMatrix(pos) * rotMatrix(rot) * transMatrix(target_dist);

  target_pos.x() = m(0, 3);
  target_pos.y() = m(1, 3);
  target_pos.z() = m(2, 3);
}
