#include "display.h"
#include "sphere.h"

namespace display
{
    // last parameter corresponds to the distance between the camera and the projection plane
    std::tuple<float, float, float> canvasToViewport(int x, int y, int Vw, int Vh, int Cw, int Ch, float d)
    {
        std::tuple<float, float, float> tup = std::make_tuple(x * Vw / (Cw * 1.0), y * Vh / (Ch * 1.0), d);
        return tup;
    }

    // std::vector<unsigned char> generatePixelArray(int canvasWidth, int canvasHeight, int viewPortWidth, int viewPortHeight)
    // {
    //     float inf = std::numeric_limits<float>::infinity();
    //     Eigen::Vector3d O(0.0, 0.0, 0.0);
    //     Eigen::Vector3d D(0, 0, 0);
    //     Eigen::Vector3d center(0, 0, 30);
    //     Sphere teste = Sphere(center, 5.0, std::make_tuple(255, 0, 0));

    //     std::vector<unsigned char> pixelVector;
    //     for (int i = -canvasWidth / 2; i < canvasWidth / 2; i++)
    //     {
    //         for (int j = -canvasHeight / 2; j < canvasHeight / 2; j++)
    //         {
    //             std::tuple<float, float, float> T = display::canvasToViewport(j, i, viewPortWidth, viewPortHeight, canvasWidth, canvasHeight, 1);

    //             D(0) = std::get<0>(T);
    //             D(1) = std::get<1>(T);
    //             D(2) = std::get<2>(T);
    //             std::tuple<int, int, int> color = utils::traceRay(O, D, 1, inf, teste);

    //             // std::cout << std::get<0>(color) / 255;
    //             pixelVector.push_back(std::get<0>(color));
    //             pixelVector.push_back(std::get<1>(color));
    //             pixelVector.push_back(std::get<2>(color));
    //         }
    //     }
    //     return pixelVector;
    // }

}
