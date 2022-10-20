#ifndef DIRECTIONAL_H_
#define DIRECTIONAL_H_

#include "lightSource.h"
class Directional : public LightSource {
 public:
  Directional(Eigen::Vector3d I_F, Eigen::Vector4d D_F)
      : LightSource(I_F), D_F(D_F) {}
  Eigen::Vector4d getDF();
  std::tuple<Eigen::Vector3d, Eigen::Vector3d> calculateL(Eigen::Vector3d,
                                                          Eigen::Vector3d); 

 private:
  Eigen::Vector4d D_F;
};

#endif
