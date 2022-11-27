#ifndef LIGHTSOURCE_H_
#define LIGHTSOURCE_H_

#include <eigen3/Eigen/Dense>
#include <tuple>

class LightSource {
   public:
    enum lightTypes { POINT,
                      SPOTLIGHT,
                      DIRECTIONAL };

    LightSource(Eigen::Vector3d I_F) : I_F(I_F) {}
    Eigen::Vector3d getIF();
    virtual Eigen::Vector3d getPF() { return Eigen::Vector3d(0.0, 0.0, 0.0); };
    virtual std::tuple<Eigen::Vector3d, Eigen::Vector3d> calculateL(
        Eigen::Vector3d, Eigen::Vector3d) {
        return std::make_tuple(Eigen::Vector3d(0.0, 0.0, 0.0),
                               Eigen::Vector3d(0.0, 0.0, 0.0));
    }
    virtual Eigen::Vector3d getIA() { return Eigen::Vector3d(0.0, 0.0, 0.0); }
    virtual double getDistance(Eigen::Vector3d) = 0;
    virtual void translate(double x, double y, double z, Eigen::Matrix4d wc) = 0;

   private:
    Eigen::Vector3d I_F;
};
#endif