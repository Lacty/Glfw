
#pragma once
#include <vector>
#include <GLFW/glfw3.h>
#include <Pico/picojson.h>


class Loader {
private:
  std::string          path;
  std::vector<GLfloat> vtx;

public:
  Loader() = default;
  Loader(const std::string& path);

  void load();
  void save(const std::vector<GLfloat>& vtx);
  void setPath(const std::string& path);

  const std::vector<GLfloat>& getVtx() const;
};
