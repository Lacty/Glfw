
#include <iostream>
#include <GLFW/glfw3.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "maker/maker.hpp"


static int WIDTH  = 640;
static int HEIGHT = 480;

void resize(GLFWwindow* window,
            const int width,
            const int height)
{
  WIDTH  = width;
  HEIGHT = height;
}

float toRadians(float deg) {
  return (deg * M_PI) / 180.0f;
}

Eigen::Matrix4f perspView(float fovy,
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

int main() {
  
}
