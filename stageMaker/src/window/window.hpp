
#pragma once


namespace window {

static int WIDTH;
static int HEIGHT;

} // --- window


void setWindowSize(int width, int height);

int getWindowWidth() const;

int getWindowHeight() const;

float getWindowAspect() const;
