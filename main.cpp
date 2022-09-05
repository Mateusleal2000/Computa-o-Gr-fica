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
    double radius = 0.5;
    double dWindow = 1;
    double x = 0;
    double y = 0;
    double z = -(dWindow + radius);
    double canvasWidth = 500;
    double canvasHeight = 500;
    double viewPortWidth = 1;
    double viewPortHeight = 1;
    double nRow = 500;
    double nCol = 500;

    Eigen::Vector3d O(0.0, 0.0, 0.0);
    Eigen::Vector3d center(x, y, z);
    Eigen::Vector3d I_F(0.7, 0.7, 0.7);
    Eigen::Vector3d P_F(0, 5, 0);
    Eigen::Vector3d K(1, 1, 1);

    displayStructs::Viewport viewport(viewPortWidth, viewPortHeight, nRow, nCol, dWindow);
    displayStructs::LightSource lS(I_F, P_F);
    Sphere s1(utilsStructs::Color(255, 0, 0), center, K, radius);

    std::vector<std::shared_ptr<Sphere>> spheres;
    std::vector<std::shared_ptr<displayStructs::LightSource>> lightSources;

    spheres.push_back(std::make_shared<Sphere>(s1));
    lightSources.push_back(std::make_shared<displayStructs::LightSource>(lS));

    std::vector<int> pixelVector = display::scene(viewport, O, lightSources, spheres);
    std::string output = "output.ppm";

    display::draw(canvasWidth, canvasHeight, pixelVector, output);
}