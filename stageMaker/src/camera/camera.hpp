
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
  float near;
  float far;

  Eigen::Matrix4f perspView();
  
  void lookAt();
  void perspTrans();

  void translation();
  void rotation();

public:
  Camera() = default;
  Camera(Eigen::Vector3f pos,
         Eigen::Vector3f target_pos);

  void update();

  void setPos(const Eigen::Vector3f& pos);
  void setRot(const Eigen::Vector3f& rot);
  void setUp(const Eigen::Vector3f& up);
  void setTargetPos(const Eigen::Vector3f& target_pos);
  
  void setFovy(float fovy);
  void setNear(float near);
  void setFar(float far);

  Eigen::Vector3f getPos() const;
  Eigen::Vector3f getRot() const;
  Eigen::Vector3f getUp() const;
  Eigen::Vector3f getTargetPos() const;

  float getFovy() const;
  float getNear() const;
  float getFar() const;
};
