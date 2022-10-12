#ifndef TEXTURE_UTILS_H
#define TEXTURE_UTILS_H

#include <Magick++.h>
#include <vector>

namespace textureUtils {
enum TEXTURE_MODE { FILL, REPEAT, DEFAULT };
std::vector<double> getTextureRGB(std::string path);
};  // namespace textureUtils
#endif