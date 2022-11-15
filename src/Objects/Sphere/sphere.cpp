#include "sphere.h"

#include <eigen3/Eigen/Dense>
#include <iostream>

std::tuple<double, double> Sphere::intersectRay(Eigen::Vector3d O,
                                                Eigen::Vector3d D) {
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

    double t1 = (-b + std::sqrt(delta)) / (2.0 * a);
    double t2 = (-b - std::sqrt(delta)) / (2.0 * a);

    return std::make_tuple(t1, t2);
}

double Sphere::getRadius() { return radius; }

Eigen::Vector3d Sphere::getCenter() { return center; }

Eigen::Vector3d Sphere::getNormal(Eigen::Vector3d P_I) {
    return ((P_I - this->center) / this->radius);
}

void Sphere::scale(double s) {
    this->radius = this->radius * s;
    return;
}

void Sphere::translate(double x, double y, double z, Eigen::Matrix4d wc) {
    Eigen::Vector4d aux_center(x, y, z, 1);
    Eigen::Vector4d new_center = wc * aux_center;
    this->center(0) = new_center(0);
    this->center(1) = new_center(1);
    this->center(2) = new_center(2);
    this->wc = wc;
    return;
}

Sphere Sphere::reflection(matrix::REFLECTION_AXIS axis) {
    Eigen::Matrix4d m = matrix::reflection(axis);
    Eigen::Vector4d aux(this->center(0), this->center(1), this->center(2), 1);
    Eigen::Vector4d aux2 = m * aux;
    Sphere reflectedSphere(this->getK(), this->getM(), this->radius,
                           aux2.head<3>());

    return reflectedSphere;
}