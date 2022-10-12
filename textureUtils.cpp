#include "textureUtils.h"

namespace textureUtils {
std::vector<double> getTextureRGB(std::string path) {
  Magick::Image image;
  image.read(path);
  int w = image.baseColumns();
  int h = image.baseRows();

  Magick::Quantum *pixels = image.getPixels(0, 0, w, h);
  std::vector<double> pixelsRGB;

  int row = 0;
  int column = 0;

  for (int x = 0; x < w; x++) {
    for (int y = 0; y < h; y++) {
      Magick::ColorRGB rgb(image.pixelColor(x, y));
      pixelsRGB.push_back(rgb.red());
      pixelsRGB.push_back(rgb.green());
      pixelsRGB.push_back(rgb.blue());
    }
  }

  return pixelsRGB;
}
}  // namespace utils
