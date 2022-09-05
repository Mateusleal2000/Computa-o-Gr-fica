#ifndef OBJECT_H_
#define OBJECT_H_

#include <tuple>
#include <eigen3/Eigen/Dense>
#include "utilsStructs.h"

class Object
{
public:
    utilsStructs::Color getColor();
    Eigen::Vector3d getCenter();
    Eigen::Vector3d getK();

protected:
    Object(utilsStructs::Color color, Eigen::Vector3d center, Eigen::Vector3d k) : color(color), center(center), K(k){};

    utilsStructs::Color color;
    Eigen::Vector3d center;
    Eigen::Vector3d K;
};

#endif