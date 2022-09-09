#include "sphere.h"

#include <eigen3/Eigen/Dense>
#include <iostream>

std::tuple<double, double> Sphere::intersectRay(Eigen::Vector3d O, Eigen::Vector3d D) {
    double a, b, c;
    double delta;
    double r = this->radius;
    double inf = std::numeric_limits<double>::infinity();
    Eigen::Vector3d w = O - this->getCenter();

    a = D.dot(D);
    b = 2 * (w.dot(D));
    c = w.dot(w) - (r * r);

    delta = (b * b) - (4 * a * c);

    if (delta < 0) {
        return std::make_tuple(inf, inf);
    }

    double t1 = (-b + std::sqrt(delta)) / (2 * a);
    double t2 = (-b - std::sqrt(delta)) / (2 * a);

    return std::make_tuple(t1, t2);
}

double Sphere::getRadius() {
    return radius;
}

Eigen::Vector3d Sphere::getCenter() {
    return center;
}

Eigen::Vector3d Sphere::getNormal(Eigen::Vector3d P_I) {
    return ((P_I - this->center) / this->radius);
}