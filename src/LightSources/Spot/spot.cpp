#include "spot.h"

Eigen::Vector4d Spot::getDS() { return this->D_S; }
Eigen::Vector4d Spot::getPS() { return this->P_S; }
double Spot::getTheta() { return this->theta; }

std::tuple<Eigen::Vector3d, Eigen::Vector3d> Spot::calculateL(
    Eigen::Vector3d P_I, Eigen::Vector3d n) {
    Eigen::Vector3d I_F = this->getIF();
    Eigen::Vector3d l(0, 0, 0);
    l = (this->getPS().head<3>() - P_I).normalized();
    double clds = l.dot(-(this->getDS().head<3>()).normalized());
    if (clds >= std::cos(theta)) {
        I_F = I_F * clds;
    } else {
        I_F = I_F * 0.0;
    }
    return std::make_tuple(l, I_F);
}

double Spot::getDistance(Eigen::Vector3d P_I) {
    return (this->getPF() - P_I).norm();
}

void Spot::translate(double x, double y, double z, Eigen::Matrix4d wc) {
    // this->P_S(0) = x;
    // this->P_S(1) = y;
    // this->P_S(2) = z;
    // this->P_S = this->P_S * wc;
}