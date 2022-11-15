
#ifndef SCENE_H_
#define SCENE_H_

#include <eigen3/Eigen/Dense>
#include <memory>
#include <vector>

#include "../Display/displayStructs.h"
#include "../LightSources/LightSource/lightSource.h"
#include "../Objects/Object/object.h"
#include "../Utils/utils.h"

class Scene {
   public:
    Scene(displayStructs::Viewport viewport, displayStructs::Camera camera,
          std::vector<std::shared_ptr<LightSource>> lightSources,
          std::vector<std::shared_ptr<Object>> objects)
        : viewport(viewport),
          camera(camera),
          lightSources(lightSources),
          objects(objects) {}

    std::vector<unsigned char> display(bool isPerspective);
    std::shared_ptr<Object> pick(Eigen::Vector3d O, Eigen::Vector3d D, std::vector<std::shared_ptr<Object>>);
    std::vector<std::shared_ptr<Object>> getObjects();
    displayStructs::Viewport getViewport();

   private:
    displayStructs::Viewport viewport;
    displayStructs::Camera camera;
    std::vector<std::shared_ptr<LightSource>> lightSources;
    std::vector<std::shared_ptr<Object>> objects;
};
#endif