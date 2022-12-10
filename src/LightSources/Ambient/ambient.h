#ifndef AMBIENT_H_
#define AMBIENT_H_

#include "../LightSource/lightSource.h"
class Ambient : public LightSource {
   public:
    Ambient(double I_A)
        : LightSource(Eigen::Vector3d(0.0, 0.0, 0.0)),
          I_A(Eigen::Vector3d(I_A, I_A, I_A)) {}
    Eigen::Vector3d getIA();
    double getDistance(Eigen::Vector3d P_I);
    void translate(double x, double y, double z, Eigen::Matrix4d wc);
    void returnToWorld(Eigen::Matrix4d cw);

   private:
    Eigen::Vector3d I_A;
};
#endif