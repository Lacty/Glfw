
#include "loader.hpp"
#include <sstream>
#include <fstream>


Loader::Loader(const std::string& path) :
path(path) {}


void Loader::load() {
  std::stringstream ss;
  std::ifstream      f;

  // load
  f.open(path.c_str(), std::ios::binary);
  if (!f) {
    std::cout << "file not opened" << std::endl;
  }

  // convert to stringstream
  ss << f.rdbuf();
  f.close();

  picojson::value v;
  ss >> v;

  auto obj = v.get<picojson::object>();
  
  // extraction "vertex"
  auto array = obj["vertex"].get<picojson::array>();

  vtx.clear();
  for (auto it : array) {
    vtx.push_back(it.get<double>());
  }
}

void Loader::save(const std::vector<GLfloat>& vtx) {
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

void Loader::setPath(const std::string& path) {
  this->path = path;
}


const std::vector<GLfloat>& Loader::getVtx() const {
  return vtx;
}
