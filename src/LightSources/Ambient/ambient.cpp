#include "ambient.h"

Eigen::Vector3d Ambient::getIA() { return this->I_A; }
double Ambient::getDistance(Eigen::Vector3d P_I) { return -1; }