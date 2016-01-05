
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


Eigen::Matrix4f Camera::perspView(float fovy,
                                  float aspect,
                                  float near,
                                  float far)
{
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

  Eigen::Matrix4f m = perspView(fovy, aspect, near, far);
  glMultMatrixf(m.data());

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}
