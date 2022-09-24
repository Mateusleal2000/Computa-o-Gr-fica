#ifndef CONE_H_
#define CONE_H_

#include <Eigen/Dense>
#include <memory>
#include <tuple>

#include "displayStructs.h"
#include "object.h"
#include "plane.h"
#include "utilsStructs.h"

class Cone : public Object {
  enum INTERSECTION_TYPE { BASE, SURFACE };

 public:
  Cone(utilsStructs::materialK k, double shininess, double radius,
       Eigen::Vector3d center, double height, Eigen::Vector3d dCone)
      : Object(k, shininess),
        radius(radius),
        center(center),
        height(height),
        coneDir(dCone) {
    vertex = center + coneDir * height;
    baseLid = std::make_unique<Plane>(k, shininess, center, -coneDir);
  };

  Cone(utilsStructs::materialK k, double shininess, double radius,
       Eigen::Vector3d center, Eigen::Vector3d vertex)
      : Object(k, shininess), radius(radius), center(center), vertex(vertex) {
    height = (vertex - center).norm();
    coneDir = (vertex - center) / (vertex - center).norm();
    baseLid = std::make_unique<Plane>(k, shininess, center, -coneDir);
  };

  double getRadius();
  Eigen::Vector3d getCenter();
  Eigen::Vector3d getNormal(Eigen::Vector3d P_I);
  std::tuple<double, double> intersectRay(Eigen::Vector3d, Eigen::Vector3d);

 private:
  INTERSECTION_TYPE intersectionType;
  double radius;
  double height;
  Eigen::Vector3d center;
  Eigen::Vector3d coneDir;
  Eigen::Vector3d vertex;
  std::unique_ptr<Plane> baseLid;

  double onSurface(Eigen::Vector3d, Eigen::Vector3d, double, double);
};
#endif