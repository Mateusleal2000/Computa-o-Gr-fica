#ifndef UTILS_H_
#define UTILS_H_

#include <memory>
#include <tuple>
#include <limits>
#include <eigen3/Eigen/Dense>
#include "utilsStructs.h"
#include "displayStructs.h"
#include "object.h"
#include "sphere.h"

class Sphere;
namespace utils
{
    std::tuple<double, double> intersectRaySphere(Eigen::Vector3d, Eigen::Vector3d, std::shared_ptr<Sphere>);
    std::tuple<double, double, double> traceRay(Eigen::Vector3d, Eigen::Vector3d, std::vector<std::shared_ptr<displayStructs::LightSource>>, std::vector<std::shared_ptr<Object>>);
}

#endif