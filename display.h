#include <tuple>
#include <vector>
#include <limits>
#include <eigen3/Eigen/Dense>
#include "utils.h"

class Sphere;
namespace display
{
    std::tuple<float, float, float> canvasToViewport(int x, int y, int Vw, int Vh, int Cw, int Ch, float d);
    std::vector<unsigned char> generatePixelArray(int canvasWidth, int canvasHeight, int viewPortWidth, int viewPortHeight);
}
