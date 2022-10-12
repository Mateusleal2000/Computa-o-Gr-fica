#ifndef OBJECT_H_
#define OBJECT_H_

#include <Eigen/Dense>
#include <memory>
#include <tuple>

#include "displayStructs.h"
#include "textureUtils.h"
#include "utilsStructs.h"

class Object {
 public:
  virtual std::tuple<double, double> intersectRay(Eigen::Vector3d,
                                                  Eigen::Vector3d) = 0;
  virtual Eigen::Vector3d getNormal(Eigen::Vector3d) = 0;
  utilsStructs::materialK getK();
  double getM();

 protected:
  Object(utilsStructs::materialK k, double m, std::string path = "",
         textureUtils::TEXTURE_MODE mode = textureUtils::TEXTURE_MODE::DEFAULT)
      : K(k), m(m), mode(mode) {
    if (path != "" && mode != textureUtils::TEXTURE_MODE::DEFAULT) {
      //std::cout << path << " " << mode << "\n";
      imageRGB = textureUtils::getTextureRGB(path);
    }
  };

  utilsStructs::materialK K;
  double m;
  std::vector<double> imageRGB;
  textureUtils::TEXTURE_MODE mode;
};

#endif