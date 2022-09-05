#ifndef SPHERE_H_
#define SPHERE_H_

#include <tuple>
#include <eigen3/Eigen/Dense>
#include "utilsStructs.h"
#include "object.h"

class Sphere : public Object
{
public:
    Sphere(utilsStructs::Color color, Eigen::Vector3d center, Eigen::Vector3d k, double radius) : Object(color, center, k), radius(radius){};
    double getRadius();

private:
    double radius;
};
#endif