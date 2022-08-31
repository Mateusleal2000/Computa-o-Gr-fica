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
    float radius = 1;
    float dJanela = 1;
    float z = -(dJanela + radius);
    Eigen::Vector3d center(-1, 0, z);
    Sphere s = Sphere(center, radius, std::make_tuple(255, 0, 0));

    int canvasWidth = 500;
    int canvasHeight = 500;
    int viewPortWidth = 3;
    int viewPortHeight = 3;
    int nLin = 500;
    int nCol = 500;
    std::vector<unsigned char> pixelVector;

    // for (int i = 0; i < canvasWidth; i++)
    // {
    //     for (int j = 0; j < canvasHeight; j++)
    //     {
    //         std::tuple<float, float, float> T = display::canvasToViewport(j, i, viewPortWidth, viewPortHeight, canvasWidth, canvasHeight, 1);

    //         D(0) = std::get<0>(T);
    //         D(1) = std::get<1>(T);
    //         D(2) = std::get<2>(T);
    //         std::tuple<int, int, int> color = utils::traceRay(O, D, 1, inf, teste);

    //         // std::cout << std::get<0>(color) / 255;
    //         pixelVector.push_back(std::get<0>(color));
    //         pixelVector.push_back(std::get<1>(color));
    //         pixelVector.push_back(std::get<2>(color));
    //     }
    // }

    float deltaX = viewPortWidth / nCol * 1.0;
    float deltaY = viewPortHeight / nLin * 1.0;
    float x, y;

    for (int i = 0; i < nLin; i++)
    {
        // y = (viewPortHeight / 2 * 1.0) - (deltaY / 2) - (i * deltaY);
        for (int j = 0; j < nCol; j++)
        {
            x = -(viewPortWidth / 2 * 1.0) + (deltaX / 2) + (j * deltaX);
            // std::tuple<float, float, float> T = display::canvasToViewport(j, i, viewPortWidth, viewPortHeight, canvasWidth, canvasHeight, -dJanela);
            // D(0) = std::get<0>(T);
            // D(1) = std::get<1>(T);
            // D(2) = std::get<2>(T);

            D(0) = x - O(0);
            D(1) = y - O(1);
            D(2) = -dJanela;
            std::tuple<int, int, int> color = utils::traceRay(O, D, -dJanela, inf, s);

            pixelVector.push_back(std::get<0>(color));
            pixelVector.push_back(std::get<1>(color));
            pixelVector.push_back(std::get<2>(color));
        }
    }

    unsigned char *pix = pixelVector.data();
    // unsigned char *pix = display::generatePixelArray(canvasWidth, canvasHeight, viewPortWidth, viewPortHeight).data();

    InitializeMagick(*argv);
    Image image;
    image.read(canvasWidth, canvasHeight, "RGB", CharPixel, pix);

    image.write("result.png");
}