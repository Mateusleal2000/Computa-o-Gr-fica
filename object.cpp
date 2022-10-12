#include "object.h"

#include <iostream>

utilsStructs::materialK Object::getK() { return K; }

double Object::getM() { return m; }

textureUtils::TEXTURE_MODE Object::getMode() { return mode; }

utilsStructs::Texel Object::getPixel(double x, double z) {
  // utilsStructs::Texel tex(0,0,0);

  int imgW = imageRGB.size();
  int imgH = imageRGB[0].size();

  double fx = (x - (-200)) / 400;
  double fz = (z - (-400)) / 400;

  /*for (auto lista : imageRGB) {
    for (auto tex : lista) {
      std::cout << tex.R << " " << tex.G << " " << tex.B << "\n";
    }
  }*/
  int indexX = 0 + fx * (imgW - 1);
  int indexZ = 0 + fz * (imgH - 1);

  // int mapX = x % imgH;
  // int mapY = y % imgW;

  return imageRGB[indexX][indexZ];
}