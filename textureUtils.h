#ifndef TEXTURE_UTILS_H
#define TEXTURE_UTILS_H

#include <Magick++.h>

#include <vector>

#include "utilsStructs.h"

namespace textureUtils {
enum TEXTURE_MODE { FILL, REPEAT, DEFAULT };
std::vector<std::vector<utilsStructs::Texel>> getTextureRGB(std::string path);
};  // namespace textureUtils
#endif