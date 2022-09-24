
#ifndef SCENE_H_
#define SCENE_H_

#include <memory>
#include <vector>

#include "displayStructs.h"
#include "object.h"

class Scene {
 public:
  Scene(displayStructs::Viewport viewport, displayStructs::Camera camera,
        std::vector<std::shared_ptr<displayStructs::LightSource>> lightSources,
        std::vector<std::shared_ptr<Object>> objects)
      : viewport(viewport),
        camera(camera),
        lightSources(lightSources),
        objects(objects) {}

  std::vector<unsigned char> display();

 private:
  displayStructs::Viewport viewport;
  displayStructs::Camera camera;
  std::vector<std::shared_ptr<displayStructs::LightSource>> lightSources;
  std::vector<std::shared_ptr<Object>> objects;
};
#endif