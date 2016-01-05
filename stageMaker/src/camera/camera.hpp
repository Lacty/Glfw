
#pragma once
#include <Eigen/Core>
#include <Eigen/Geometry>


class Camera {
private:
  Eigen::Vector3f pos;
  Eigen::Vector3f rot;
  Eigen::Vector3f up;
  Eigen::Vector3f target_pos;

  float fovy;
  float aspect;
  float near;
  float far;

  Eigen::Matrix4f perspView(float fovy,
                            float aspect,
                            float near,
                            float far);
  
  void perspTrans();

  void translate();
  void rotate();

public:
  Camera() = default;
  Camera(Eigen::Vector3f pos,
         Eigen::Vector3f target_pos);

  void update();

  void setPos(Eigen::Vector3f pos);
  void setRot(Eigen::Vector3f rot);
  void setUp(Eigen::Vector3f up);
  void setTargetPos(Eigen::Vector3f target_pos);
  
  void setFovy(float fovy);
  void setAspect(float aspect);
  void setNear(float near);
  void setFar(float far);

  Eigen::Vector3f getPos();
  Eigen::Vector3f getRot();
  Eigen::Vector3f getUp();
  Eigen::Vector3f getTargetPos();

  float getFovy();
  float getAspect();
  float getNear();
  float getFar();
};
