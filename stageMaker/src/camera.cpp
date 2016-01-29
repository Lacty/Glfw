
#include "../include/camera.hpp"
#include "../include/utility.hpp"
#include <GLFW/glfw3.h>
#include <Eigen/Geometry>


Camera::Camera(const vec3f& pos, const vec3f& target) :
pos(pos),
up(0.0f, 1.0f, 0.0f),
target(target),
forward(target - pos),
fovy(35.0f),
near(0.5f),
far(50.0f),
translateSpeedScale(0.2),
rotateSpeedScale(0.2) {}


void Camera::perspView() {
  float f = 1 / std::tan(toRadians(fovy) * 0.5f);
  float g = -((far + near) / (far - near));
  float h = -((2 * far * near) / (far - near));
  float i = f / getAspect();

  mat4f m;
  m <<    i,  0.0f,  0.0f,  0.0f,
       0.0f,     f,  0.0f,  0.0f,
       0.0f,  0.0f,     g,     h,
       0.0f,  0.0f,    -1,  0.0f;
  
  glMultMatrixf(m.data());
}

void Camera::perspTrans() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  perspView();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Camera::lookAt() {
  vec3f a  = pos - target;
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
  TwAddVarRW(twBar, "pos",         TW_TYPE_DIR3F, &pos,     "");
  TwAddVarRW(twBar, "target",      TW_TYPE_DIR3F, &target,  "");
  TwAddVarRW(twBar, "forward",     TW_TYPE_DIR3F, &forward, "");
  TwAddVarRW(twBar, "transSpeed",  TW_TYPE_FLOAT, &translateSpeedScale, "");
  TwAddVarRW(twBar, "rotateSpeed", TW_TYPE_FLOAT, &rotateSpeedScale,    "");
  rotateSpeedScale = 0.2f;
}

void Camera::update() {
  perspTrans();
  lookAt();
  
  forward = target - pos;
  forward.normalize();
}

void Camera::translate(const vec3f& dist) {
  vec3f side = forward.cross(up);
  side.normalize();

  vec3f acc = side * dist.x() + forward * dist.z();
  acc *= translateSpeedScale;
  
  pos    = Eigen::Translation<float, 3>(acc) * pos;
  target = Eigen::Translation<float, 3>(acc) * target;
}

void Camera::rotate(const vec3f& quant) {
  Eigen::Quaternionf vertically;
  vertically = Eigen::AngleAxisf(toRadians(quant.x() * rotateSpeedScale), up.normalized());
  
  Eigen::Quaternionf horizontally;
  horizontally = Eigen::AngleAxisf(toRadians(quant.y() * rotateSpeedScale), forward.cross(up).normalized());

  Eigen::Translation<float, 3> translation(pos);

  target = translation * vertically * horizontally * forward;
}
