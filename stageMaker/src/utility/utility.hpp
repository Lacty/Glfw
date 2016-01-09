
#pragma once
#include <cmath>
#include <Eigen/Core>


float toRadians(float deg);

Eigen::Matrix4f rotMatrix(float x, float y, float z);
