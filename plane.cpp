#include "plane.h"

Eigen::Vector3d Plane::getNormal(Eigen::Vector3d P_I) {
    return this->nBar;
}

std::tuple<double, double> Plane::intersectRay(Eigen::Vector3d O, Eigen::Vector3d D) {
    Eigen::Vector3d w = O - this->pPI;
    double t = -(w.dot(this->nBar) / D.dot(this->nBar));
    return std::make_tuple(t, t);
}
