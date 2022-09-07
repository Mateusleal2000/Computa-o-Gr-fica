#ifndef DISPLAYSTRUCTS_H_
#define DISPLAYSTRUCTS_H_

#include <eigen3/Eigen/Dense>

namespace displayStructs
{
    struct Viewport
    {
        double width;
        double height;
        double nRows;
        double nColumns;
        double dWindow;

        Viewport(double w, double h, double r, double c, double dW) : width(w), height(h), nRows(r), nColumns(c), dWindow(dW) {}
    };

    struct Canvas
    {
        double width;
        double height;

        Canvas(double w, double h) : width(w), height(h) {}
    };

    struct Camera
    {
        Eigen::Vector3d O;
        Eigen::Vector3d I_A;
        Camera(Eigen::Vector3d O, Eigen::Vector3d I_A) : O(O), I_A(I_A) {}
    };

    struct LightSource
    {
        Eigen::Vector3d I_F;
        Eigen::Vector3d P_F;
        LightSource(Eigen::Vector3d I_F, Eigen::Vector3d P_F) : I_F(I_F), P_F(P_F) {}
    };
}
#endif