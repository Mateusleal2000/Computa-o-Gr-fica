#include <Magick++.h>
#include <iostream>
#include <tuple>
#include <limits>
#include <cmath>
#include <vector>
#include "sphere.h"
#include "utils.h"
#include "display.h"
#include <eigen3/Eigen/Dense>

using namespace Magick;

int main(int argc, char **argv)
{
    double inf = std::numeric_limits<double>::infinity();
    double radius = 30;
    double dWindow = 1;
    double z = -(dWindow + radius);
    Eigen::Vector3d O(0.0, 0.0, 0.0);
    Eigen::Vector3d D(0, 0, 0);
    Eigen::Vector3d center(0, 0, z);
    Sphere s = Sphere(center, radius, std::make_tuple(255, 0, 0));

    double canvasWidth = 500;
    double canvasHeight = 500;
    double viewPortWidth = 50;
    double viewPortHeight = 50;
    double nRow = 500;
    double nCol = 500;
    double deltaX = viewPortWidth / nCol;
    double deltaY = viewPortHeight / nRow;
    double x, y;
    std::vector<unsigned char> pixelVector;

    for (int r = 0; r < nRow; r++)
    {
        y = (viewPortHeight / 2) - (deltaY / 2) - (r * deltaY);
        for (int c = 0; c < nCol; c++)
        {
            x = -(viewPortWidth / 2) + (deltaX / 2) + (c * deltaX);
            D(0) = x - O(0);
            D(1) = y - O(1);
            D(2) = -dWindow;
            std::tuple<int, int, int> color = utils::traceRay(O, D, -dWindow, inf, s);

            pixelVector.push_back(std::get<0>(color));
            pixelVector.push_back(std::get<1>(color));
            pixelVector.push_back(std::get<2>(color));
        }
    }

    unsigned char *pix = pixelVector.data();

    InitializeMagick(*argv);
    Image image;
    image.read(canvasWidth, canvasHeight, "RGB", CharPixel, pix);

    image.write("result.png");
}