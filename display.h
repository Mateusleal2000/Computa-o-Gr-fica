#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <eigen3/Eigen/Dense>
#include <fstream>
#include <limits>
#include <memory>
#include <tuple>
#include <vector>

#include "displayStructs.h"
#include "object.h"
#include "utils.h"

class Sphere;
namespace display {
std::vector<int> scene(displayStructs::Viewport, displayStructs::Camera, std::vector<std::shared_ptr<displayStructs::LightSource>>, std::vector<std::shared_ptr<Object>>);
int draw(double, double, std::vector<int>, std::string);
}  // namespace display

#endif