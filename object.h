#ifndef OBJECT_H_
#define OBJECT_H_

#include <tuple>
#include <eigen3/Eigen/Dense>
#include "utilsStructs.h"

class Object
{
public:
    Object(double dWindow, utilsStructs::Color color, Eigen::Vector3d center, Eigen::Vector3d K) : dWindow(dWindow), color(color), center(center), K(K) {}

    double getDWindow();
    utilsStructs::Color getColor();
    Eigen::Vector3d getCenter();
    Eigen::Vector3d getK();

private:
    double dWindow;
    utilsStructs::Color color;
    Eigen::Vector3d center;
    Eigen::Vector3d K;
};

#endif