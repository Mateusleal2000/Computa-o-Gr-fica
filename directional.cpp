#include "directional.h"

Eigen::Vector4d Directional::getDF() { return this->D_F; }
std::tuple<Eigen::Vector3d, Eigen::Vector3d> Directional::calculateL(
    Eigen::Vector3d P_I, Eigen::Vector3d n) {
  Eigen::Vector3d l(0, 0, 0);
  Eigen::Vector3d I_F = this->getIF();
  l = getDF().head<3>().normalized() * -1;
  //if (l.dot(n) >= 0) {
  //  I_F = I_F * 0;
  //}
  return std::make_tuple(l, I_F);
}
