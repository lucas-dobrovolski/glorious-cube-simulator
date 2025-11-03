#pragma once
#include <vector>
#include "Cube.h"
#include <algorithm>  // para std::find

class World 
{
public:
  std::vector<Cube*> cubes;
  World() = default;
  
  ~World() {
    for(auto obj : cubes) delete obj;
  }

  void add(Cube* obj) {
    cubes.push_back(obj);
  }

  
  void remove(Cube* obj) {
    auto it = std::find(cubes.begin(), cubes.end(), obj);
    if(it != cubes.end()) cubes.erase(it);
  }

  size_t size() const { return cubes.size(); }


};

