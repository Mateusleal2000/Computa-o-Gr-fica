#ifndef POINT_H_
#define POINT_H_

#include "../LightSource/lightSource.h"
class Point : public LightSource {
   public:
    Point(Eigen::Vector3d I_F, Eigen::Vector3d P_F)
        : LightSource(I_F), P_F(P_F) {}
    Eigen::Vector3d getPF();
    std::tuple<Eigen::Vector3d, Eigen::Vector3d> calculateL(Eigen::Vector3d,
                                                            Eigen::Vector3d);
    double getDistance(Eigen::Vector3d);

   private:
    Eigen::Vector3d P_F;
};

#endif
