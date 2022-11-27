#include "directional.h"

Eigen::Vector4d Directional::getDF() { return this->D_F; }
std::tuple<Eigen::Vector3d, Eigen::Vector3d> Directional::calculateL(
    Eigen::Vector3d P_I, Eigen::Vector3d n) {
    Eigen::Vector3d l(0, 0, 0);
    Eigen::Vector3d I_F = this->getIF();
    l = this->getDF().head<3>().normalized() * -1;
    // std::cout << n(0) << " " << n(1) << " " << n(2) << "\n";
    if (this->getDF().head<3>().dot(n) >= 0.0) {
        I_F = I_F * 0.0;
    }
    return std::make_tuple(l, I_F);
}
Eigen::Vector3d getPF() {
    return Eigen::Vector3d(INFINITY, INFINITY, INFINITY);
};

double Directional::getDistance(Eigen::Vector3d) { return INFINITY; }
void Directional::translate(double x, double y, double z, Eigen::Matrix4d wc) {
}