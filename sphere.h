#ifndef SPHERE_H_
#define SPHERE_H_

#include <Eigen/Dense>
#include <memory>
#include <tuple>

#include "displayStructs.h"
#include "object.h"
#include "utilsStructs.h"

class Sphere : public Object {
   public:
    Sphere(utilsStructs::Color color, utilsStructs::materialK k, double shininess, double radius, Eigen::Vector3d center) : Object(color, k, shininess), radius(radius), center(center){};
    double getRadius();
    Eigen::Vector3d getCenter();
    Eigen::Vector3d getNormal(Eigen::Vector3d P_I);
    std::tuple<double, double> intersectRay(Eigen::Vector3d, Eigen::Vector3d);

   private:
    Eigen::Vector3d center;
    double radius;
};
#endif