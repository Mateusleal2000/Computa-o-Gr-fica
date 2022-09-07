#include <iostream>
#include <memory>
#include <vector>
#include "sphere.h"
#include "plane.h"
#include "utils.h"
#include "display.h"
#include "displayStructs.h"
#include "utilsStructs.h"
#include <eigen3/Eigen/Dense>

int main(int argc, char **argv)
{
    double radius = 40;
    double dWindow = 30;
    double x = 0;
    double y = 0;
    double z = -(dWindow + radius);
    double canvasWidth = 500;
    double canvasHeight = 500;
    double viewPortWidth = 60;
    double viewPortHeight = 60;
    double nRow = 500;
    double nCol = 500;

    Eigen::Vector3d O(0.0, 0.0, 0.0);
    Eigen::Vector3d center(x, y, z);
    Eigen::Vector3d I_A(0.3, 0.3, 0.3);
    Eigen::Vector3d I_F(0.7, 0.7, 0.7);
    Eigen::Vector3d P_F(0, 60, -30);

    Eigen::Vector3d Ke(0.7, 0.2, 0.2);
    Eigen::Vector3d Ka(0.7, 0.2, 0.2);
    Eigen::Vector3d Kd(0.7, 0.2, 0.2);

    utilsStructs::materialK K(Ke, Ka, Kd);

    displayStructs::Viewport viewport(viewPortWidth, viewPortHeight, nRow, nCol, dWindow);
    displayStructs::LightSource lS(I_F, P_F);
    displayStructs::Camera camera(O, I_A);

    std::vector<std::shared_ptr<displayStructs::LightSource>> lightSources;
    std::vector<std::shared_ptr<Object>> objects;

    // Eigen::Vector3d center1(0, 0.5, z);
    Eigen::Vector3d center1(0, 0, -100);
    Eigen::Vector3d center2(0.6, -0.4, z);
    Eigen::Vector3d center3(-0.6, -0.4, z);

    // objetos válidos
    objects.push_back(std::make_shared<Sphere>(Sphere(utilsStructs::Color(255, 0, 0), K, 10, radius, center1)));
    // objects.push_back(std::make_shared<Plane>(Plane(utilsStructs::Color(100), K, 10, Eigen::Vector3d(0, -radius, 0), Eigen::Vector3d(0, 1, 0))));

    lightSources.push_back(std::make_shared<displayStructs::LightSource>(lS));

    std::vector<int> pixelVector = display::scene(viewport, camera, lightSources, objects);
    std::string output = "output.ppm";

    display::draw(canvasWidth, canvasHeight, pixelVector, output);
}