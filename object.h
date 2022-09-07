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
    virtual std::tuple<double, double> intersectRay(Eigen::Vector3d, Eigen::Vector3d) = 0;
    virtual std::tuple<double, double> calculateLighting(std::shared_ptr<displayStructs::LightSource>, displayStructs::Camera, Eigen::Vector3d, double) = 0;
    utilsStructs::Color getColor();
    utilsStructs::materialK getK();
    double getM();

protected:
    Object(utilsStructs::Color color, utilsStructs::materialK k, double m) : color(color), K(k), m(m){};

    utilsStructs::Color color;
    utilsStructs::materialK K;
    double m;
};

#endif