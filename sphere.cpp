#include "sphere.h"

std::tuple<double, double> Sphere::intersectRay(Eigen::Vector3d O, Eigen::Vector3d D)
{
    double a, b, c;
    double delta;
    double r = this->radius;
    double inf = std::numeric_limits<double>::infinity();

    a = D.dot(D);
    b = 2 * (this->getCenter().dot(D));
    c = this->getCenter().dot(this->getCenter()) - (r * r);

    delta = (b * b) - (4 * a * c);

    if (delta < 0)
    {
        return std::make_tuple(inf, inf);
    }

    double t1 = (-b + std::sqrt(delta)) / (2 * a);
    double t2 = (-b - std::sqrt(delta)) / (2 * a);

    return std::make_tuple(t1, t2);
}

std::tuple<double, double> Sphere::calculateLighting(std::shared_ptr<displayStructs::LightSource> lS, displayStructs::Camera camera, Eigen::Vector3d D, double t)
{

    Eigen::Vector3d P_I(0, 0, 0);
    Eigen::Vector3d n(0, 0, 0);
    Eigen::Vector3d l(0, 0, 0);
    Eigen::Vector3d r(0, 0, 0);
    Eigen::Vector3d v(0, 0, 0);
    Eigen::Vector3d center = this->getCenter();

    P_I = camera.O + t * (D - camera.O);
    n = (P_I - center) / this->getRadius();
    l = (lS.get()->P_F - P_I) / (lS.get()->P_F - P_I).norm();
    r = 2 * ((l.dot(n)) * n) - l;
    v = -D / D.norm();

    double F_D = std::max(n.dot(l), 0.0);
    double F_E = std::max(r.dot(v), 0.0);
    return std::make_tuple(F_D, F_E);
}

double Sphere::getRadius()
{
    return radius;
}