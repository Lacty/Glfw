
#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <Pico/picojson.h>
#include "vector.hpp"


class Loader {
private:
  std::string path;
  std::vector<float> vertices;
  std::vector<float> colors;

public:
  Loader(const std::string& path) : path(path) {}
  Loader() = default;

  Loader(const Loader&) = delete;
  Loader& operator =(const Loader&) = delete;


  void load() {
    std::stringstream ss;
    std::ifstream      f;

    f.open(path.c_str(), std::ios::binary);
    if (!f.is_open()) {
      std::cout << "file wasn't opened" << std::endl;
      exit(1);
    }

    ss << f.rdbuf();
    f.close();

    picojson::value v;
    ss >> v;

    auto obj = v.get<picojson::object>();

    auto array_vtx = obj["vertices"].get<picojson::array>();
    auto array_col = obj["colors"].get<picojson::array>();

    vertices.clear();
    for (const auto& it : array_vtx) {
      vertices.push_back(it.get<double>());
    }

    colors.clear();
    for (const auto& it : array_col) {
      colors.push_back(it.get<double>());
    }
  }

  void save(const std::vector<float>& _vertices,
            const std::vector<float>& _colors)
  {
    picojson::object obj;
    picojson::array  array;
  
    vertices = _vertices;
    colors   = _colors;

    for (const auto& it : vertices) {
      array.emplace_back(picojson::value(it));
    }
  
    // add vertices
    obj.insert(std::make_pair("vertices", picojson::value(array)));

    array.clear();
    for (const auto& it : colors) {
      array.emplace_back(picojson::value(it));
    }

    // add colors
    obj.insert(std::make_pair("colors", picojson::value(array)));

    // convert to value
    picojson::value json(obj);

    // save
    std::ofstream ofs(path.c_str());
    ofs << json.serialize().c_str();
  }

  const std::vector<float>& getVertices() const {
    return vertices;
  }

  const std::vector<float>& getColors() const {
    return colors;
  }
};
