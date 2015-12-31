
#include <iostream>
#include <GLFW/glfw3.h>
#include <Eigen/Core>
#include <Eigen/Geometry>


static int WIDTH = 640;
static int HEIGHT = 480;

void resize(GLFWwindow* window,
            const int width,
            const int height)
{
  WIDTH = width;
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
  float g = -((far +  near) / (far - near));
  float h = -((2 * far * near) / (far - near));
  float i = f / aspect;

  Eigen::Matrix4f m;
  m <<    i,  0.0f,  0.0f,  0.0f,
       0.0f,     f,  0.0f,  0.0f,
       0.0f,  0.0f,     g,     h,
       0.0f,  0.0f,    -1,  0.0f;

  return m;
}

Eigen::Matrix4f lookAt(const Eigen::Vector3f& eye,
                       const Eigen::Vector3f& target,
                       const Eigen::Vector3f& up)
{
  Eigen::Vector3f a  = eye - target;
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
  T << 1.0f, 0.0f, 0.0f, -eye.x(),
       0.0f, 1.0f, 0.0f, -eye.y(),
       0.0f, 0.0f, 1.0f, -eye.z(),
       0.0f, 0.0f, 0.0f,     1.0f;
  
  return R * T;
}

void perspTrans() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  float aspect = WIDTH / float(HEIGHT);
  Eigen::Matrix4f m = perspView(36, aspect, 0.5f, 50.0f);
  glMultMatrixf(m.data());

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

auto main()->int {
  if (!glfwInit()) return -1;

  GLFWwindow* window;
  window = glfwCreateWindow(640, 480, "camera", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetWindowSizeCallback(window, resize);

  while(!glfwWindowShouldClose(window)) {
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    perspTrans();


    // Camera
    static Eigen::Vector3f cam_pos(0.0f, 0.0f,   0.0f);
    static Eigen::Vector3f cam_rot(0.0f, 0.0f,   0.0f);
    static Eigen::Vector3f tar_pos(0.0f, 0.0f, -10.0f);
    static Eigen::Vector3f  cam_up(0.0f, 1.0f,   0.0f);

    Eigen::Matrix4f cm = lookAt(cam_pos, tar_pos, cam_up);
    glMultMatrixf(cm.data());

    cam_rot.y() += 0.2f;

    glRotatef(-cam_rot.x(), 1.0f, 0.0f, 0.0f);
    glRotatef(-cam_rot.y(), 0.0f, 1.0f, 0.0f);
    glRotatef(-cam_rot.z(), 0.0f, 0.0f, 1.0f);

    glTranslatef(-cam_pos.x(), -cam_pos.y(), -cam_pos.z());


    GLfloat vtx[] = {
      0.0f, 0.433f, 0.0f,
      -0.5f, -0.433f, 0.0f,
      0.5f, -0.433f, 0.0f
    };

    glTranslatef(0.0f, 0.0f, -10.0f);

    glColor4f(0.4f, 0.3f, 0.6f, 1.0f);
    glVertexPointer(3, GL_FLOAT, 0, vtx);

    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
