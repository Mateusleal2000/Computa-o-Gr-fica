#ifndef UTILS_H_
#define UTILS_H_

#include <Eigen/Dense>
#include <algorithm>
#include <limits>
#include <memory>
#include <tuple>
#include <vector>

#include "displayStructs.h"
#include "object.h"
#include "sphere.h"
#include "utilsStructs.h"

class Sphere;
namespace utils {
utilsStructs::Color traceRay(
    displayStructs::Camera camera, Eigen::Vector3d,
    std::vector<std::shared_ptr<displayStructs::LightSource>>,
    std::vector<std::shared_ptr<Object>>);

std::tuple<double, std::shared_ptr<Object>> closestIntersection(
    Eigen::Vector3d, Eigen::Vector3d, double, double,
    std::vector<std::shared_ptr<Object>>);

std::tuple<double, double, double> calculateLighting(
    std::vector<std::shared_ptr<displayStructs::LightSource>> lightSources,
    displayStructs::Camera camera, Eigen::Vector3d D, double t,
    std::shared_ptr<Object> closestObject,
    std::vector<std::shared_ptr<Object>> objects);

bool isLightBlocked(std::shared_ptr<Object> closestObject,
                    std::vector<std::shared_ptr<Object>> objects,
                    Eigen::Vector3d P_I,
                    std::shared_ptr<displayStructs::LightSource> lS,
                    Eigen::Vector3d l);
}  // namespace utils

#endif