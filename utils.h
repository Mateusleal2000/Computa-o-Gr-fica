#include <tuple>
#include <eigen3/Eigen/Dense>

class Sphere;
namespace utils
{
    std::tuple<double, double> intersectRaySphere(Eigen::Vector3d O, Eigen::Vector3d D, Sphere s);
    std::tuple<int, int, int> traceRay(Eigen::Vector3d O, Eigen::Vector3d D, double tMin, double tMax, Sphere &s);
}
