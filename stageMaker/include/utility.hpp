
#pragma once
#include <cmath>
#include "vector.hpp"


float toRadians(float deg) {
  return (deg * M_PI) / 180.0f;
}

mat4f rotMatrix(const vec3f& vec) {
  float x = toRadians(vec.x());
  float y = toRadians(vec.y());
  float z = toRadians(vec.z());

  Eigen::Matrix4f matX;
  matX << 1,           0,            0, 0,
          0, std::cos(x), -std::sin(x), 0,
          0, std::sin(x),  std::cos(x), 0,
          0,           0,            0, 1;

  Eigen::Matrix4f matY;
  matY <<  std::cos(y), 0, std::sin(y), 0,
                     0, 1,           0, 0,
          -std::sin(y), 0, std::cos(y), 0,
                     0, 0,           0, 1;

  Eigen::Matrix4f matZ;
  matZ << std::cos(z), -std::sin(y), 0, 0,
          std::sin(z),  std::cos(y), 0, 0,
                    0,            0, 1, 0,
                    0,            0, 0, 1;

  return matX * matY * matZ;
}

mat4f transMatrix(const vec3f& vec) {
  float x = vec.x();
  float y = vec.y();
  float z = vec.z();
 
  Eigen::Matrix4f m;
  m << 1, 0, 0, x,
       0, 1, 0, y,
       0, 0, 1, z,
       0, 0, 0, 1;

  return m;
}

double toSita(const vec2f& v1, const vec2f& v2) {
  double cosSita = v1.dot(v2) / (v1.norm() * v2.norm());
  double sita = acos(cosSita);
  sita = sita * 180.0 / M_PI;
  return sita;
}
