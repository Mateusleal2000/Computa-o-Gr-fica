#include "point.h"

#include <iostream>

Eigen::Vector3d Point::getPF() { return this->P_F; }
std::tuple<Eigen::Vector3d, Eigen::Vector3d> Point::calculateL(
    Eigen::Vector3d P_I, Eigen::Vector3d n) {
    Eigen::Vector3d l(0, 0, 0);
    Eigen::Vector3d P_F = this->getPF();
    l = (P_F - P_I) / (P_F - P_I).norm();

    return std::make_tuple(l, this->getIF());
}

double Point::getDistance(Eigen::Vector3d P_I) {
    return (this->P_F - P_I).norm();
}

void Point::translate(double x, double y, double z, Eigen::Matrix4d wc) {
    Eigen::Vector4d auxPF(x, y, z, 1.0);
    auxPF = wc * auxPF;
    this->P_F = auxPF.head<3>();
}