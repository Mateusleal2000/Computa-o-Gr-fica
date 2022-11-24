
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
          std::vector<std::shared_ptr<Object>> objects, bool isPerspective)
        : viewport(viewport),
          camera(camera),
          orthCamera(camera),
          lightSources(lightSources),
          objects(objects),
          isPerspective(isPerspective) {}

    std::vector<std::shared_ptr<Object>> objects;
    std::vector<unsigned char> display();
    std::shared_ptr<Object> pick(Eigen::Vector3d O, Eigen::Vector3d D, std::vector<std::shared_ptr<Object>>);
    std::vector<std::shared_ptr<Object>> getObjects();
    displayStructs::Viewport getViewport();
    Eigen::Vector3d getCamera();
    bool getProjection();
    void switchProjection();
    void setOrigin(double x, double y, double z);

   private:
    bool isPerspective;
    displayStructs::Viewport viewport;
    displayStructs::Camera camera;
    displayStructs::Camera orthCamera;
    std::vector<std::shared_ptr<LightSource>> lightSources;
};
#endif