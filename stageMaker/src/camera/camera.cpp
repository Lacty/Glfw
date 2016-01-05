
#include "camera.hpp"
#include "../utility/utility.hpp"
#include <GLFW/glfw3.h>


Camera::Camera(Eigen::Vector3f pos,
               Eigen::Vector3f target_pos) :
pos(pos),
rot(0.0f, 0.0f, 0.0f),
up(0.0f, 1.0f, 0.0f),
target_pos(target_pos),
fovy(35.0f),
aspect(1.333f),
near(0.5f),
far(50.0f) {}


Eigen::Matrix4f Camera::perspView() {
  float f = 1 / std::tan(toRadians(fovy) * 0.5f);
  float g = -((far + near) / (far - near));
  float h = -((2 * far * near) / (far - near));
  float i = f / aspect;

  Eigen::Matrix4f m;
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

void Camera::translation() {
  glTranslatef(-pos.x(), -pos.y(), -pos.z());
}

void Camera::rotation() {
  glRotatef(-rot.x(), 1.0f, 0.0f, 0.0f);
  glRotatef(-rot.y(), 0.0f, 1.0f, 0.0f);
  glRotatef(-rot.z(), 0.0f, 0.0f, 1.0f);
}

void Camera::lookAt() {
  Eigen::Vector3f a  = pos - target_pos;
  Eigen::Vector3f z_ = a / a.norm();

  Eigen::Vector3f b  = up.cross(z_);
  Eigen::Vector3f x_ = b / b.norm();

  Eigen::Vector3f y_ = z_.cross(x_);

  Eigen::Matrix4f R;
  R << x_.x(), x_.y(), x_.z(), 0.0f,
       y_.x(), y_.y(), y_.z(), 0.0f,
       z_.x(), z_.y(), z_.z(), 0.0f,
         0.0f,   0.0f,   0.0f, 1.0f;

  Eigen::Matrix4f T;
  T << 1.0f, 0.0f, 0.0f, -pos.x(),
       0.0f, 1.0f, 0.0f, -pos.y(),
       0.0f, 0.0f, 1.0f, -pos.z(),
       0.0f, 0.0f, 0.0f,     1.0f;
 
  Eigen::Matrix4f m = R * T;
  glMultMatrixf(m.data());
}


void Camera::update() {
  perspTrans();
  lookAt();
  rotation();
  translation();
}
