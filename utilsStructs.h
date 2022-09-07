#ifndef UTILSSTRUCTS_H_
#define UTILSSTRUCTS_H_

#include <eigen3/Eigen/Dense>

namespace utilsStructs
{
    struct Color
    {
        Color(int bg) : R(bg), G(bg), B(bg){

                                      };
        Color(int red, int green, int blue) : R(red), G(green), B(blue)
        {
        }
        int R;
        int G;
        int B;
    };

    struct materialK
    {
        materialK(Eigen::Vector3d ke, Eigen::Vector3d ka, Eigen::Vector3d kd) : Ke(ke), Ka(ka), Kd(kd){};
        Eigen::Vector3d Ke;
        Eigen::Vector3d Ka;
        Eigen::Vector3d Kd;
    };
}

#endif