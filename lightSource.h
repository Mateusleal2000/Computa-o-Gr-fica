//#define _USE_MATH_DEFINES
#ifndef LIGHTSOURCE_H_
#define LIGHTSOURCE_H_

#include <Eigen/Dense>
//#include <cmath>

class LightSource {
 public:
  enum lightTypes { POINT, SPOTLIGHT, DIRECTIONAL };
  LightSource(Eigen::Vector3d I_F, Eigen::Vector3d P_F) : I_F(I_F), P_F(P_F) {
    this->type = lightTypes::POINT;
    this->theta = 0.0;
  }
  LightSource(Eigen::Vector3d I_F, Eigen::Vector4d D_F) : I_F(I_F), D_F(D_F) {
    this->type = lightTypes::DIRECTIONAL;
    this->theta = 0.0;
  }
  LightSource(Eigen::Vector3d I_F, Eigen::Vector4d P_I, Eigen::Vector4d P_S,
              double angle)
      : I_F(I_F), P_S(P_S), theta(angle) {
    this->type = lightTypes::SPOTLIGHT;
    this->D_S = (P_I - P_S).normalized();
    //this->theta = angle * M_PI / 180;
  }

  Eigen::Vector3d getIF();
  Eigen::Vector3d getPF();
  Eigen::Vector4d getDF();
  Eigen::Vector4d getDS();
  Eigen::Vector4d getPS();
  double getTheta();
  lightTypes getType();

 private:
  lightTypes type;
  Eigen::Vector3d I_F;
  Eigen::Vector3d P_F;
  Eigen::Vector4d D_F;
  Eigen::Vector4d D_S;
  Eigen::Vector4d P_S;
  double theta;
};
#endif