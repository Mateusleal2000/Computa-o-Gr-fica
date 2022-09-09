#include "plane.h"

Eigen::Vector3d Plane::getNormal(Eigen::Vector3d P_I)
{
    return this->nBar;
}

std::tuple<double, double> Plane::intersectRay(Eigen::Vector3d O, Eigen::Vector3d D)
{
    Eigen::Vector3d w = O - this->pPI;
    double t = -(w.dot(this->nBar) / D.dot(this->nBar));
    return std::make_tuple(t, t);
}

std::tuple<double, double> Plane::calculateLighting(std::shared_ptr<displayStructs::LightSource> lS, displayStructs::Camera camera, Eigen::Vector3d D, double t)
{
    Eigen::Vector3d P_I(0, 0, 0);
    Eigen::Vector3d l(0, 0, 0);
    Eigen::Vector3d r(0, 0, 0);
    Eigen::Vector3d v(0, 0, 0);

    P_I = camera.O + t * (D - camera.O);
    l = (lS.get()->P_F - P_I) / (lS.get()->P_F - P_I).norm();
    r = 2 * ((l.dot(this->nBar)) * this->nBar) - l;
    v = -D / D.norm();

    double F_D = std::max(this->nBar.dot(l), 0.0);
    double F_E = std::max(std::pow(r.dot(v), this->getM()), 0.0);
    return std::make_tuple(F_D, F_E);
}
