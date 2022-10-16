#include "lightSource.h"

#include <iostream>

Eigen::Vector3d LightSource::getIF() { return this->I_F; }

Eigen::Vector3d LightSource::getPF() { return this->P_F; }
Eigen::Vector4d LightSource::getDF() { return this->D_F; }
Eigen::Vector4d LightSource::getDS() { return this->D_S; }
Eigen::Vector4d LightSource::getPS() { return this->P_S; }
double LightSource::getTheta() { return this->theta; }
LightSource::lightTypes LightSource::getType() { return this->type; }