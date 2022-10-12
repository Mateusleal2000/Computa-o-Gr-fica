#include "textureUtils.h"

#include "utilsStructs.h"

namespace textureUtils {
std::vector<std::vector<utilsStructs::Texel>> getTextureRGB(std::string path) {
  Magick::Image image;
  image.read(path);
  int w = image.baseColumns();
  int h = image.baseRows();

  Magick::Quantum *pixels = image.getPixels(0, 0, w, h);
  std::vector<std::vector<utilsStructs::Texel>> pixelsRGB;

  int row = 0;
  int column = 0;

  for (int x = 0; x < w; x++) {
    std::vector<utilsStructs::Texel> aux;
    for (int y = 0; y < h; y++) {
      Magick::ColorRGB rgb(image.pixelColor(x, y));
      aux.push_back(utilsStructs::Texel(rgb.red(), rgb.green(), rgb.blue()));
    }
    pixelsRGB.push_back(aux);
  }

  return pixelsRGB;
}
}  // namespace textureUtils
