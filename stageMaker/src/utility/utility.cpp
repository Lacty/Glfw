
#include "utility.hpp"


float toRadians(float deg) {
  return (deg * M_PI) / 180.0f;
}

Eigen::Matrix4f rotMatrix(float x, float y, float z) {
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

Eigen::Matrix4f transMatrix(float x, float y, float z) {
  Eigen::Matrix4f m;
  m << 1, 0, 0, x,
       0, 1, 0, y,
       0, 0, 1, z,
       0, 0, 0, 1;

  return m;
}
