#include "sphere.h"

double Sphere::getRadius()
{
    return radius;
}
Eigen::Vector3d Sphere::getCenter()
{
    return center;
}
std::tuple<double, double, double> Sphere::getColor()
{
    return color;
}