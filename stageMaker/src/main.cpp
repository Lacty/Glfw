
#include <iostream>
#include <GLFW/glfw3.h>
#include <Eigen/Core>
#include <Eigen/Geometry>

#include "camera/camera.hpp"
#include "window/window.hpp"
#include "maker/maker.hpp"
#include "input/input.hpp"


void resize(GLFWwindow* window,
            const int width,
            const int height)
{
  setWindowSize(width, height);
}

bool isOpen(GLFWwindow* window, const Key& key) {
  return !glfwWindowShouldClose(window) && !key.isPush(Keys::Esc);
}

auto main()->int {
  if (!glfwInit()) return -1;

  setWindowSize(640, 480);

  GLFWwindow* window;
  window = glfwCreateWindow(getWindowWidth(), getWindowHeight(),
                            "stageMaker", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetWindowSizeCallback(window, resize);


  Camera camera({{ 0.0f, 0.0f,   0.0f },
                 { 0.0f, 0.0f, -10.0f }});
  camera.setNear(0.5f);
  camera.setFar(50.0f);

  Mouse  mouse;
  Key    key;
  Maker  maker("assets/stage.json", camera, mouse, key);

  float angle = 0.0f;
  float rotate = 0.0f;

  while (isOpen(window, key)) {
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    
    {// UI ---
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    GLfloat vtx1[] = {
      0.0f, 0.433f, 0.0f,
      -0.5f, -0.433f, 0.0f,
      0.5f, -0.433f, 0.0f
    };
    
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.8f, 0.5f, 0.0f);
    glScalef(0.03f, 0.03f, 0.03f);
    glTranslatef(-camera.getPos().x(),
                 -camera.getPos().z(),
                 0.0f);

    glRotatef(camera.getRot().y(), 0.0f, 0.0f, 1.0f);

    glVertexPointer(3, GL_FLOAT, 0, vtx1);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();
    }// --- UI
    

    glPushMatrix();
    camera.update();
    mouse.update(window);
    key.update(window);

    if (key.isPress(Keys::A)) {
      camera.moveVector(1, 0, 0);
    } else if (key.isPress(Keys::D)) {
      camera.moveVector(-1, 0, 0);
    }
    if (key.isPress(Keys::Z)) {
      rotate += 2.1f;
    } else if (key.isPress(Keys::X)) {
      rotate -= 0.1f;
    }

    camera.setRot(Eigen::Vector3f(0.0f, rotate, 0.0f));

   
    // Draw ---
    glPushMatrix();
    GLfloat vtx[] = {
      0.0f, 0.433f, 0.0f,
      -0.5f, -0.433f, 0.0f,
      0.5f, -0.433f, 0.0f
    };

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glTranslatef(0.0f, 0.0f, -10.0f);

    glPointSize(50);
    glVertexPointer(3, GL_FLOAT, 0, vtx);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);
    
    glPopMatrix();
    // --- Draw

    glPopMatrix();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
