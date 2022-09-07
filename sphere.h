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
    //~Sphere(){};
    Sphere(utilsStructs::Color color, Eigen::Vector3d center, Eigen::Vector3d k, double radius) : Object(color, center, k), radius(radius){};
    double getRadius();
    std::tuple<double, double> intersectRay(Eigen::Vector3d, Eigen::Vector3d);
    std::tuple<double, double> calculateLighting(std::shared_ptr<displayStructs::LightSource>, displayStructs::Camera, Eigen::Vector3d, double);

private:
    double radius;
};
#endif