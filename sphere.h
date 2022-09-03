#ifndef SPHERE_H_
#define SPHERE_H_

#include <tuple>
#include <eigen3/Eigen/Dense>
#include "utilsStructs.h"
class Sphere
{
public:
    Sphere(Eigen::Vector3d center, double radius, utilsStructs::Color color)
    {
        this->center = center;
        this->radius = radius;
        this->color = color;
    };
    ~Sphere(){};
    double getRadius();
    Eigen::Vector3d getCenter();
    utilsStructs::Color getColor();

private:
    Eigen::Vector3d center;
    double radius;
    utilsStructs::Color color;
};
#endif