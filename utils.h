#ifndef UTILS_H_
#define UTILS_H_

#include <tuple>
#include <limits>
#include <eigen3/Eigen/Dense>
#include "utilsStructs.h"

class Sphere;
namespace utils
{
    std::tuple<double, double> intersectRaySphere(Eigen::Vector3d O, Eigen::Vector3d D, Sphere s);
    std::tuple<double, double, double> traceRay(Eigen::Vector3d O, Eigen::Vector3d D, Eigen::Vector3d I_F, Eigen::Vector3d P_F, Eigen::Vector3d K, Sphere &s);
}

#endif