#include <Magick++.h>
#include <iostream>
#include <tuple>
#include <cmath>
#include <algorithm>
#include <vector>
#include "sphere.h"
#include "utils.h"
#include "display.h"
#include <eigen3/Eigen/Dense>

using namespace Magick;

int main(int argc, char **argv)
{
    double radius = 0.5;
    double dWindow = 1;
    double x = 0;
    double y = 0;
    double z = -(dWindow + radius);

    Eigen::Vector3d O(0.0, 0.0, 0.0);
    Eigen::Vector3d D(0, 0, 0);
    Eigen::Vector3d center(x, y, z);
    Eigen::Vector3d I_F(0.7, 0.7, 0.7);
    Eigen::Vector3d P_F(0, 5, 0);
    Eigen::Vector3d K(1, 1, 1);
    Sphere s = Sphere(center, radius, std::make_tuple(255, 0, 0));

    double canvasWidth = 500;
    double canvasHeight = 500;
    double viewPortWidth = 1;
    double viewPortHeight = 1;
    double nRow = 500;
    double nCol = 500;

    std::vector<unsigned char> pixelVector = display::scene(viewPortWidth, viewPortHeight, nRow, nCol, dWindow, O, D, I_F, P_F, K, s);

    unsigned char *pix = pixelVector.data();

    InitializeMagick(*argv);
    Image image;
    image.read(canvasWidth, canvasHeight, "RGB", CharPixel, pix);

    image.write("result.png");
}