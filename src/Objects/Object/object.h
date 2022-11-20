#ifndef OBJECT_H_
#define OBJECT_H_

#include <eigen3/Eigen/Dense>
#include <memory>
#include <tuple>

#include "../../Display/displayStructs.h"
#include "../../Utils/utilsStructs.h"

class Object {
   public:
    virtual std::tuple<double, double> intersectRay(Eigen::Vector3d,
                                                    Eigen::Vector3d) = 0;
    virtual Eigen::Vector3d getNormal(Eigen::Vector3d) = 0;
    virtual void returnToWorld(Eigen::Matrix4d cw) = 0;
    utilsStructs::materialK getK();
    double getM();
    utilsStructs::Texel getPixel(double x, double z);
    virtual void translate(double x, double y, double z, Eigen::Matrix4d wc) = 0;

   protected:
    Object(utilsStructs::materialK k, double m)
        : K(k), m(m){};

    utilsStructs::materialK K;
    double m;
    std::vector<std::vector<utilsStructs::Texel>> imageRGB;
};

#endif