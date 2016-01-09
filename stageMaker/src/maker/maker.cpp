
#include "maker.hpp"
#include "../camera/camera.hpp"
#include "../input/mouse.hpp"
#include "../input/key.hpp"


Maker::Maker(const std::string& path,
             Camera& camera,
             Mouse& mouse,
             Key& key) :
camera(camera),
mouse(mouse),
key(key),
loader(path)
{
  std::cout << "create Maker" << std::endl;

  loader.load();

  stage_vertex  = loader.getVtx();
  editing_index = stage_vertex.size();
}


void Maker::update() {}

void Maker::draw() {}
