#ifndef OBJECT_H_
#define OBJECT_H_

#include <tuple>
#include <memory>
#include <eigen3/Eigen/Dense>
#include "utilsStructs.h"
#include "displayStructs.h"

class Object
{
public:
    //~Object(){};
    virtual std::tuple<double, double> intersectRay(Eigen::Vector3d, Eigen::Vector3d) = 0;
    virtual std::tuple<double, double> calculateLighting(std::shared_ptr<displayStructs::LightSource>, Eigen::Vector3d, Eigen::Vector3d, double) = 0;
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