#ifndef SPOT_H_
#define SPOT_H_
#define M_PI 3.14159265358979323846

#include "../LightSource/lightSource.h"
class Spot : public LightSource {
   public:
    Spot(Eigen::Vector3d I_F, Eigen::Vector4d P_I, Eigen::Vector4d P_S,
         double angle)
        : LightSource(I_F), P_S(P_S), theta(angle) {
        this->D_S = (P_I - P_S).normalized();
        this->theta = angle * M_PI / 180;
    };
    Eigen::Vector4d getDS();
    Eigen::Vector4d getPS();
    double getTheta();
    std::tuple<Eigen::Vector3d, Eigen::Vector3d> calculateL(Eigen::Vector3d,
                                                            Eigen::Vector3d);
    double getDistance(Eigen::Vector3d P_I);

   private:
    Eigen::Vector4d D_S;
    Eigen::Vector4d P_S;
    double theta;
};
#endif