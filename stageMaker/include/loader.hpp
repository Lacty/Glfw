
#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <list>
#include <Pico/picojson.h>
#include "vector.hpp"


class Loader {
private:
  std::string path;
  std::list<float> vtx;

public:
  Loader(const std::string& path) : path(path) {}

  // this class can't copy
  Loader() = delete;
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

    auto array = obj["vertex"].get<picojson::array>();

    vtx.clear();
    for (auto it : array) {
      vtx.push_back(it.get<double>());
    }
  }

  void save(const std::list<float>& vtx) {
    picojson::object obj;
    picojson::array  array;
  
    for (auto it : vtx) {
      array.emplace_back(picojson::value(it));
    }
  
    // make object
    obj.insert(std::make_pair("vector", picojson::value(array)));

    // convert to value
    picojson::value json(obj);

    // save
    std::ofstream ofs(path.c_str());
    ofs << json.serialize().c_str();
  }

  const std::list<float>& getVtx() const {
    return vtx;
  }
};
