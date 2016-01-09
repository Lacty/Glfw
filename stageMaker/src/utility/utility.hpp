
#pragma once
#include <cmath>
#include <Eigen/Core>


float toRadians(float deg);

Eigen::Matrix3f rotMatrix(float x, float y, float z);

Eigen::Matrix4f transMatrix(float x, float y, float z);
