#include <tuple>
#include <vector>
#include <limits>
#include <eigen3/Eigen/Dense>
#include "utils.h"

class Sphere;
namespace display
{
    std::vector<int> scene(double viewPortWidth, double viewPortHeight, double nRow, double nCol, double dWindow, Eigen::Vector3d O, Eigen::Vector3d D, Eigen::Vector3d I_F, Eigen::Vector3d P_F, Eigen::Vector3d K, Sphere s);
}
