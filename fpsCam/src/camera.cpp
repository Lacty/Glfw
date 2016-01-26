
#include "../include/camera.hpp"


float toRadians(float deg) {
  return (deg * M_PI) / 180.0f;
}


Camera::Camera(int _width, int _height,
               const vec3f& _pos,
               const vec3f& _up,
               const vec3f& _rot,
               const vec3f& _foward,
               float _fovy,
               float _near,
               float _far)
{
  pos    = _pos;
  up     = _up;
  rot    = _rot;
  foward = _foward;
  fovy   = _fovy;
  near   = _near;
  far    = _far;
  aspect = _width / float(_height);
}

void Camera::perspView() {
  float f = 1 / std::tan(toRadians(fovy) * 0.5f);
  float g = -((far +  near) / (far - near));
  float h = -((2 * far * near) / (far - near));
  float i = f / aspect;

  Eigen::Matrix4f m;
  m <<    i,  0.0f,  0.0f,  0.0f,
       0.0f,     f,  0.0f,  0.0f,
       0.0f,  0.0f,     g,     h,
       0.0f,  0.0f,    -1,  0.0f;

  glMultMatrixf(m.data());
}

void Camera::lookAt() {
  vec3f a  = pos - foward;
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

void Camera::perspTrans() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  perspView();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Camera::update() {
  perspTrans();
  lookAt();
}
