#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <GL/glut.h>

#include <Eigen/Dense>
#include <fstream>
#include <limits>
#include <memory>
#include <tuple>
#include <vector>

#include "displayStructs.h"
#include "object.h"
#include "utils.h"
#include "lightSource.h"

class Sphere;
namespace display {
std::vector<unsigned char> scene(
    displayStructs::Viewport, displayStructs::Camera,
    std::vector<std::shared_ptr<LightSource>>,
    std::vector<std::shared_ptr<Object>>);
}  // namespace display

#endif