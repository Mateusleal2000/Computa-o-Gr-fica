#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <memory>
#include <tuple>
#include <vector>
#include <limits>
#include <fstream>
#include <eigen3/Eigen/Dense>
#include "utils.h"
#include "displayStructs.h"
#include "object.h"

class Sphere;
namespace display
{
    std::vector<int> scene(displayStructs::Viewport, Eigen::Vector3d, std::vector<std::shared_ptr<displayStructs::LightSource>>, std::vector<std::shared_ptr<Sphere>>);
    int draw(double, double, std::vector<int>, std::string);
}

#endif