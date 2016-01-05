
#include "window.hpp"


void setWindowSize(int width, int height) {
  window::WIDTH  = width;
  window::HEIGHT = height;
}

int getWindowWidth() const {
  return window::WIDTH;
}

int getWindowHeight() const {
  return window::HEIGHT;
}

float getWindowAspect() const {
  return getWindowWidth() / float(getWindowHeight());
}
