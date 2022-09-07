#ifndef SPHERE_H_
#define SPHERE_H_

#include <tuple>
#include <memory>
#include <eigen3/Eigen/Dense>
#include "utilsStructs.h"
#include "displayStructs.h"
#include "object.h"

class Sphere : public Object
{
public:
    Sphere(utilsStructs::Color color, utilsStructs::materialK k, double shininess, double radius, Eigen::Vector3d center) : Object(color, k, shininess), radius(radius), center(center){};
    double getRadius();
    Eigen::Vector3d getCenter();
    std::tuple<double, double> intersectRay(Eigen::Vector3d, Eigen::Vector3d);
    std::tuple<double, double> calculateLighting(std::shared_ptr<displayStructs::LightSource>, displayStructs::Camera, Eigen::Vector3d, double);

private:
    Eigen::Vector3d center;
    double radius;
};
#endif