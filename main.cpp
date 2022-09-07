#include <iostream>
#include <memory>
#include <vector>
#include "sphere.h"
#include "utils.h"
#include "display.h"
#include "displayStructs.h"
#include "utilsStructs.h"
#include <eigen3/Eigen/Dense>

int main(int argc, char **argv)
{
    double radius = 0.4;
    double dWindow = 1;
    double x = 0;
    double y = 0;
    double z = -(dWindow + radius);
    double canvasWidth = 500;
    double canvasHeight = 500;
    double viewPortWidth = 3;
    double viewPortHeight = 3;
    double nRow = 500;
    double nCol = 500;

    Eigen::Vector3d O(0.0, 0.0, 0.0);
    Eigen::Vector3d center(x, y, z);
    Eigen::Vector3d I_A(0.3, 0.3, 0.3);
    Eigen::Vector3d I_F(0.7, 0.7, 0.7);
    Eigen::Vector3d P_F(0, 5, 0);
    Eigen::Vector3d K(1, 1, 1);

    displayStructs::Viewport viewport(viewPortWidth, viewPortHeight, nRow, nCol, dWindow);
    displayStructs::LightSource lS(I_F, P_F);
    displayStructs::Camera camera(O, I_A);

    std::vector<std::shared_ptr<displayStructs::LightSource>> lightSources;
    std::vector<std::shared_ptr<Object>> objects;

    Eigen::Vector3d center1(0, 0.5, z);
    Eigen::Vector3d center2(0.6, -0.4, z);
    Eigen::Vector3d center3(-0.6, -0.4, z);

    objects.push_back(std::make_shared<Sphere>(Sphere(utilsStructs::Color(255, 0, 0), center1, K, radius)));
    objects.push_back(std::make_shared<Sphere>(Sphere(utilsStructs::Color(0, 255, 0), center2, K, radius)));
    objects.push_back(std::make_shared<Sphere>(Sphere(utilsStructs::Color(0, 0, 255), center3, K, radius)));
    lightSources.push_back(std::make_shared<displayStructs::LightSource>(lS));

    std::vector<int> pixelVector = display::scene(viewport, camera, lightSources, objects);
    std::string output = "output.ppm";

    display::draw(canvasWidth, canvasHeight, pixelVector, output);
}