#ifndef OBJECT_H_
#define OBJECT_H_

#include <Eigen/Dense>
#include <memory>
#include <tuple>

#include "displayStructs.h"
#include "utilsStructs.h"

class Object {
 public:
  virtual std::tuple<double, double> intersectRay(Eigen::Vector3d,
                                                  Eigen::Vector3d) = 0;
  virtual Eigen::Vector3d getNormal(Eigen::Vector3d) = 0;
  utilsStructs::Color getColor();
  utilsStructs::materialK getK();
  double getM();

 protected:
  Object(utilsStructs::Color color, utilsStructs::materialK k, double m)
      : color(color), K(k), m(m){};

  utilsStructs::Color color;
  utilsStructs::materialK K;
  double m;
};

#endif