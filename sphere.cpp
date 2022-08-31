#include "sphere.h"

double Sphere::getRadius()
{
    return radius;
}
Eigen::Vector3d Sphere::getCenter()
{
    return center;
}
std::tuple<int, int, int> Sphere::getColor()
{
    return color;
}