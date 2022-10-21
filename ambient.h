#ifndef AMBIENT_H_
#define AMBIENT_H_

#include "lightSource.h"
class Ambient : public LightSource {
 public:
  Ambient(double I_A) : LightSource(Eigen::Vector3d(0.0,0.0,0.0)), I_A(Eigen::Vector3d(I_A,I_A,I_A)) {}
  Eigen::Vector3d getIA();

 private:
  Eigen::Vector3d I_A;
};
#endif