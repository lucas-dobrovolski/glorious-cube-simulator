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


  void drawVectorCubes(std::vector<Cube*>& cubes, Shader& shader, Camera& camera){
    shader.use();
    shader.setMat4("view", camera.getViewMatrix());
    shader.setMat4("projection", camera.getProjectionMatrix());
    for(auto obj : cubes) {
      shader.setMat4("model", obj->getModelMatrix());
      obj->draw();
  }

  }
};

