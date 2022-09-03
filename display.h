#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <tuple>
#include <vector>
#include <limits>
#include <fstream>
#include <eigen3/Eigen/Dense>
#include "utils.h"
#include "displayStructs.h"

class Sphere;
namespace display
{
    std::vector<int> scene(displayStructs::Viewport viewport, Eigen::Vector3d O, Eigen::Vector3d I_F, Eigen::Vector3d P_F, Eigen::Vector3d K, Sphere s);
    int draw(double nRow, double nCol, std::vector<int> pixelVector, std::string output);
}

#endif