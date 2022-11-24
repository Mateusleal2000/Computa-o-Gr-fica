#include "plane.h"

Eigen::Vector3d Plane::getNormal(Eigen::Vector3d P_I) { return this->nBar; }

std::tuple<double, double> Plane::intersectRay(Eigen::Vector3d O,
                                               Eigen::Vector3d D) {
    Eigen::Vector3d w = O - this->pPI;
    double t = -(w.dot(this->nBar) / D.dot(this->nBar));
    return std::make_tuple(t, t);
}

void Plane::scale(double x, double y, double z) {
    std::cout << "Eu sou inutil :P\n";
    return;
}

void Plane::translate(double x, double y, double z, Eigen::Matrix4d wc) {
}

void Plane::returnToWorld(Eigen::Matrix4d cw) {
}

void Plane::shear(double delta, matrix::SHEAR_AXIS axis) {
    return;
}

void Plane::rotate(double theta, matrix::AXIS axis) {
    std::cout << "Eu sou inutil\n";
    return;
}

void Plane::reflection(matrix::REFLECTION_AXIS axis, std::vector<std::shared_ptr<Object>> &objects) {
    return;
}