#include "plane.h"

std::tuple<double, double> Plane::intersectRay(Eigen::Vector3d O, Eigen::Vector3d D)
{
    Eigen::Vector3d w = O - this->pPI;
    double t = -(w.dot(this->nBar) / D.dot(this->nBar));
    return std::make_tuple(t, t);
}

std::tuple<double, double> Plane::calculateLighting(std::shared_ptr<displayStructs::LightSource> lS, displayStructs::Camera camera, Eigen::Vector3d D, double t)
{
    return std::make_tuple(0, 0);
}
