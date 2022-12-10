#ifndef POINT_H_
#define POINT_H_

#include "../LightSource/lightSource.h"
class Point : public LightSource {
   public:
    Point(Eigen::Vector3d I_F, Eigen::Vector3d P_F)
        : LightSource(I_F, lightTypes::POINT), P_F(P_F) {}
    Eigen::Vector3d getPF();
    std::tuple<Eigen::Vector3d, Eigen::Vector3d> calculateL(Eigen::Vector3d,
                                                            Eigen::Vector3d);
    double getDistance(Eigen::Vector3d);
    void translate(double x, double y, double z, Eigen::Matrix4d wc);
    void returnToWorld(Eigen::Matrix4d cw);

   private:
    Eigen::Vector3d P_F;
};

#endif
