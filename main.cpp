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
    // sphere equation
    //(P-C)*(P-C) = R^2
    // ray equation
    // P = O + t*D

    float inf = std::numeric_limits<float>::infinity();
    Eigen::Vector3d O(0.0, 0.0, 0.0);
    Eigen::Vector3d D(0, 0, 0);
    Eigen::Vector3d center(0, 0, 30);
    Sphere teste = Sphere(center, 5.0, std::make_tuple(255, 0, 0));

    int canvasWidth = 500;
    int canvasHeight = 500;
    int viewPortWidth = 1;
    int viewPortHeight = 1;
    std::vector<unsigned char> pixelVector;

    for (int i = -canvasWidth / 2; i < canvasWidth / 2; i++)
    {
        for (int j = -canvasHeight / 2; j < canvasHeight / 2; j++)
        {
            std::tuple<float, float, float> T = display::canvasToViewport(j, i, viewPortWidth, viewPortHeight, canvasWidth, canvasHeight, 1);

            D(0) = std::get<0>(T);
            D(1) = std::get<1>(T);
            D(2) = std::get<2>(T);
            std::tuple<int, int, int> color = utils::traceRay(O, D, 1, inf, teste);

            // std::cout << std::get<0>(color) / 255;
            pixelVector.push_back(std::get<0>(color));
            pixelVector.push_back(std::get<1>(color));
            pixelVector.push_back(std::get<2>(color));
        }
    }

    unsigned char *pix = pixelVector.data();
    // unsigned char *pix = display::generatePixelArray(canvasWidth, canvasHeight, viewPortWidth, viewPortHeight).data();

    InitializeMagick(*argv);
    Image image;
    image.read(500, 500, "RGB", CharPixel, pix);

    image.write("result.png");
}