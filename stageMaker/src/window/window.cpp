
#include "window.hpp"


void setWindowSize(int width, int height) {
  window::WIDTH  = width;
  window::HEIGHT = height;
}

int getWindowWidth() {
  return window::WIDTH;
}

int getWindowHeight() {
  return window::HEIGHT;
}

float getWindowAspect() {
  return getWindowWidth() / float(getWindowHeight());
}
