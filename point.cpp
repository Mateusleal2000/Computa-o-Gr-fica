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
  /*std::cout << this->P_F(0) << " " << this->P_F(1) << " " << this->P_F(2)
            << "\n";*/
  return (this->P_F - P_I).norm();
  //return -P_I.norm();
}
