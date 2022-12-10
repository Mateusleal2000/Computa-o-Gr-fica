#define _USE_MATH_DEFINES

#include <SDL2/SDL.h>

#include <cmath>
#include <eigen3/Eigen/Dense>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#include "Canvas/canvas.h"
#include "Display/display.h"
#include "Display/displayStructs.h"
#include "LightSources/Ambient/ambient.h"
#include "LightSources/Directional/directional.h"
#include "LightSources/LightSource/lightSource.h"
#include "LightSources/Point/point.h"
#include "LightSources/Spot/spot.h"
#include "Matrix/matrix.h"
#include "Objects/Cone/cone.h"
#include "Objects/Cylinder/cylinder.h"
#include "Objects/Mesh/mesh.h"
#include "Objects/Plane/plane.h"
#include "Objects/Sphere/sphere.h"
#include "Scene/scene.h"
#include "Utils/utils.h"
#include "Utils/utilsStructs.h"

int main(int argc, char **argv) {
    double radius = 1.0;
    double dWindow = 25;
    // double x = 0;
    // double y = 0;
    // double z = -(dWindow + radius);

    bool isPerspective = true;
    double canvasWidth = 500;
    double canvasHeight = 500;
    double viewPortWidth = isPerspective ? 60 : 1500;
    double viewPortHeight = isPerspective ? 60 : 1500;
    double nRow = 500;
    double nCol = 500;

    double lx = 450.0;
    double ly = 210.0;
    double lz = 600.0;

    double I_A = 0.3;

    Eigen::Vector4d O(lx, ly, lz, 1.0);
    Eigen::Vector4d D(0.0, 0.0, 0.0, 1.0);
    Eigen::Vector3d at(450.0, 97.5, 500.0);
    // Eigen::Vector3d at(lx, ly, 1.0);
    Eigen::Vector3d up(lx, ly + 100.0, lz);
    Eigen::Matrix4d wc = matrix::lookAt(O.head<3>(), at, up);
    Eigen::Matrix4d cw = matrix::cwMatrix(O.head<3>(), at, up);
    // std::cout << up - O.head<3>() << "\n";
    O = wc * O;
    displayStructs::Camera camera(O.head<3>(), D.head<3>());
    // Eigen::Vector3d center(x, y, z);

    Eigen::Vector3d I_F_1(0.7, 0.7, 0.7);
    Eigen::Vector4d P_F_1(300.0, 100.0, 2000.0, 1.0);
    // Eigen::Vector4d P_F_1(300.0, 294.0, 480.0, 1.0);
    Eigen::Vector3d P_F_2(100, 200, -20);

    P_F_1 = wc * P_F_1;

    Eigen::Vector3d I_F_2(0.7, 0.7, 0.7);
    Eigen::Vector4d D_F_2(-1, 0, 0, 0);

    Eigen::Vector3d I_F_3(0.7, 0.7, 0.7);
    Eigen::Vector4d P_I_3(0, 0, -25, 0);
    Eigen::Vector4d P_S_3(0, -1, -1, 1);
    Eigen::Vector4d P_S_4(0, 1, -1, 1);
    // double theta = 30;

    // sphere
    Eigen::Vector3d Ke_1(0.854, 0.647, 0.125);
    Eigen::Vector3d Ka_1(0.854, 0.647, 0.125);
    Eigen::Vector3d Kd_1(0.854, 0.647, 0.125);

    Eigen::Vector3d Ke_cherry(0.949, 0.027, 0.027);
    Eigen::Vector3d Ka_cherry(0.949, 0.027, 0.027);
    Eigen::Vector3d Kd_cherry(0.949, 0.027, 0.027);

    Eigen::Vector3d Ke_2(222.0 / 255.0, 184.0 / 255.0, 135.0 / 255.0);
    Eigen::Vector3d Ka_2(222.0 / 255.0, 184.0 / 255.0, 135.0 / 255.0);
    Eigen::Vector3d Kd_2(222.0 / 255.0, 184.0 / 255.0, 135.0 / 255.0);

    // background plane
    Eigen::Vector3d Ke_3(0.0, 0.933, 0.0);
    Eigen::Vector3d Ka_3(0.0, 0.933, 0.0);
    Eigen::Vector3d Kd_3(0.0, 0.933, 0.0);

    // cylinder
    Eigen::Vector3d Ke_4(0.745, 0.470, 0.058);
    Eigen::Vector3d Ka_4(0.745, 0.470, 0.058);
    Eigen::Vector3d Kd_4(0.745, 0.470, 0.058);

    Eigen::Vector3d Ke_plate(0.988, 0.949, 0.831);
    Eigen::Vector3d Ka_plate(0.988, 0.949, 0.831);
    Eigen::Vector3d Kd_plate(0.988, 0.949, 0.831);

    Eigen::Vector3d Ke_cake(0.388, 0.125, 0.011);
    Eigen::Vector3d Ka_cake(0.388, 0.125, 0.011);
    Eigen::Vector3d Kd_cake(0.388, 0.125, 0.011);

    Eigen::Vector3d Ke_candle(0.780, 0.729, 0.709);
    Eigen::Vector3d Ka_candle(0.780, 0.729, 0.709);
    Eigen::Vector3d Kd_candle(0.780, 0.729, 0.709);

    // cone
    Eigen::Vector3d Ke_5(0.031, 0.705, 0.329);
    Eigen::Vector3d Ka_5(0.031, 0.705, 0.329);
    Eigen::Vector3d Kd_5(0.031, 0.705, 0.329);

    // roof
    Eigen::Vector3d Ke_6(0.996, 0.364, 0.203);
    Eigen::Vector3d Ka_6(0.996, 0.364, 0.203);
    Eigen::Vector3d Kd_6(0.996, 0.364, 0.203);

    Eigen::Vector3d Ke_7(1.0, 0.078, 0.576);
    Eigen::Vector3d Ka_7(1.0, 0.078, 0.576);
    Eigen::Vector3d Kd_7(1.0, 0.078, 0.576);

    // table lid K
    Eigen::Vector3d lid_Ke(0.12, 0.51, 0.69);
    Eigen::Vector3d lid_Ka(0.12, 0.51, 0.69);
    Eigen::Vector3d lid_Kd(0.12, 0.51, 0.69);

    // table support K
    Eigen::Vector3d support_Ke(0.88, 0.52, 0.26);
    Eigen::Vector3d support_Ka(0.88, 0.52, 0.26);
    Eigen::Vector3d support_Kd(0.88, 0.52, 0.26);

    // chapeus de festa
    Eigen::Vector3d Ke_hat1(0.800, 0.610, 1.0);
    Eigen::Vector3d Ka_hat1(0.800, 0.610, 1.0);
    Eigen::Vector3d Kd_hat1(0.800, 0.610, 1.0);

    Eigen::Vector3d Ke_hat2(0.210, 0.030, 0.610);
    Eigen::Vector3d Ka_hat2(0.210, 0.030, 0.610);
    Eigen::Vector3d Kd_hat2(0.210, 0.030, 0.610);

    Eigen::Vector3d Ke_hat3(0.870, 0.030, 0.010);
    Eigen::Vector3d Ka_hat3(0.870, 0.030, 0.010);
    Eigen::Vector3d Kd_hat3(0.870, 0.030, 0.010);

    Eigen::Vector3d dCil_1(-1.0 / std::sqrt(3), 1.0 / std::sqrt(3),
                           -1.0 / std::sqrt(3));

    Eigen::Vector3d dCil_3(0, 1, 0);

    Eigen::Vector3d dCil_2(0, 1, 0.95);
    Eigen::Vector3d dCone_1(-1.0 / std::sqrt(3), 1.0 / std::sqrt(3),
                            -1.0 / std::sqrt(3));
    Eigen::Vector3d dCone_2(1.0 / std::sqrt(3), -1.0 / std::sqrt(3),
                            1.0 / std::sqrt(3));
    Eigen::Vector3d dCone_3(0.0, 1.0, 0.0);
    double height_1 = 3 * radius;
    double height_2 = radius / 3.0;

    utilsStructs::materialK K_1(Ke_1, Ka_1, Kd_1);
    utilsStructs::materialK K_2(Ke_2, Ka_2, Kd_2);
    utilsStructs::materialK K_3(Ke_3, Ka_3, Kd_3);
    utilsStructs::materialK K_4(Ke_4, Ka_4, Kd_4);
    utilsStructs::materialK K_5(Ke_5, Ka_5, Kd_5);
    utilsStructs::materialK K_6(Ke_6, Ka_6, Kd_6);
    utilsStructs::materialK K_7(Ke_7, Ka_7, Kd_7);

    utilsStructs::materialK K_hat1(Ke_hat1, Ka_hat1, Kd_hat1);
    utilsStructs::materialK K_hat2(Ke_hat2, Ka_hat2, Kd_hat2);
    utilsStructs::materialK K_hat3(Ke_hat3, Ka_hat3, Kd_hat3);

    utilsStructs::materialK K_plate(Ke_plate, Ka_plate, Kd_plate);

    utilsStructs::materialK K_cake(Ke_cake, Ka_cake, Kd_cake);

    utilsStructs::materialK K_candle(Ke_candle, Ka_candle, Kd_candle);

    utilsStructs::materialK K_cherry(Ke_cherry, Ka_cherry, Kd_cherry);

    utilsStructs::materialK lid_K(lid_Ke, lid_Ka, lid_Kd);
    utilsStructs::materialK support_K(support_Ke, support_Ka, support_Kd);

    displayStructs::Viewport viewport(viewPortWidth, viewPortHeight, nRow, nCol,
                                      dWindow);

    std::vector<std::shared_ptr<LightSource>> lightSources;
    std::vector<std::shared_ptr<Object>> objects;

    Eigen::Vector3d center1(0.0, 0.0, 0.0);
    Eigen::Vector3d center2(0.0, 0.0, 0.0);
    Eigen::Vector3d center3(0, -60, -200);
    Eigen::Vector3d center4(0, 20, -150);

    double m_1 = 10;
    double m_2 = 1;
    double m_3 = 1;

    std::string cubePath = "../resources/cube.obj";

    // Chapéus de festa
    auto party_hat1 = std::make_shared<Cone>(
        Cone(K_hat1, m_1, 1, center1, 1, dCil_3.normalized()));

    auto party_hat2 = std::make_shared<Cone>(
        Cone(K_hat2, m_1, 1, center1, 1, dCil_3.normalized()));

    auto party_hat3 = std::make_shared<Cone>(
        Cone(K_hat3, m_1, 1, center1, 1, dCil_3.normalized()));

    // Mesa
    Mesh table_lid(lid_K, m_1, cubePath);
    Mesh table_supportL(support_K, m_1, cubePath);
    Mesh table_supportR(support_K, m_1, cubePath);
    Mesh table_supportL_back(support_K, m_1, cubePath);
    Mesh table_supportR_back(support_K, m_1, cubePath);

    // Bolo
    auto plate = std::make_shared<Cylinder>(
        Cylinder(K_plate, m_1, 1, center1, 1, dCil_3.normalized()));
    auto cake = std::make_shared<Cylinder>(
        Cylinder(K_cake, m_1, 1, center1, 1, dCil_3.normalized()));
    auto candle = std::make_shared<Cylinder>(
        Cylinder(K_candle, m_1, 1, center1, 1, dCil_3.normalized()));

    Sphere cherry1(K_cherry, m_1, radius, center1);
    Sphere cherry2(K_cherry, m_1, radius, center1);
    Sphere cherry3(K_cherry, m_1, radius, center1);
    Sphere cherry4(K_cherry, m_1, radius, center1);
    Sphere cherry5(K_cherry, m_1, radius, center1);
    Sphere cherry6(K_cherry, m_1, radius, center1);
    Sphere cherry7(K_cherry, m_1, radius, center1);
    Sphere cherry8(K_cherry, m_1, radius, center1);

    // Galpao paredes
    Mesh wallL(K_2, m_1, cubePath);
    Mesh wallR(K_2, m_1, cubePath);
    Mesh back_wall(K_2, m_1, cubePath);

    // Telhado
    Mesh ceiling(K_2, m_1, cubePath);

    // arvore
    Sphere ball(K_1, m_1, radius, center1);
    auto woodBase = std::make_shared<Cylinder>(
        Cylinder(K_4, m_1, 1, center1, 1, dCil_3.normalized()));
    auto wood = std::make_shared<Cylinder>(
        Cylinder(K_4, m_1, 1, center1, 1, dCil_3.normalized()));
    auto tree = std::make_shared<Cone>(
        Cone(K_5, m_1, 1, center1, 1, dCil_3.normalized()));

    // Chao
    Eigen::Vector4d floor_pos(0.0, 0.0, 0.0, 1);
    Eigen::Vector4d floor_dir(0.0, 1.0, 0.0, 0.0);
    Plane floor(K_3, m_2, (wc * floor_pos).head<3>(),
                ((wc * floor_dir).head<3>()).normalized());

    // Posicionando mesa
    table_supportL.scale(15.0, 115.0, 15.0);
    table_supportL.translate(225.0 + 7.5, 57.5, 650.0 - 7.5, wc);

    table_supportL_back.scale(15.0, 115.0, 15.0);
    table_supportL_back.translate(225.0 + 7.5, 57.5, 350.0 + 7.5, wc);

    table_supportR.scale(15.0, 115.0, 15.0);
    table_supportR.translate(675.0 - 7.5, 57.5, 650.0 - 7.5, wc);

    table_supportR_back.scale(15.0, 115.0, 15.0);
    table_supportR_back.translate(675.0 - 7.5, 57.5, 350.0 + 7.5, wc);

    table_lid.scale(450.0, 5.0, 300.0);
    table_lid.translate(450.0, 117.5, 500.0, wc);

    // Posicionando arvore

    woodBase->scale(30.0, 9.0);
    woodBase->translate(300.0, 95.0, 500.0, wc);

    wood->scale(30.0, 40.0);
    wood->translate(300.0, 104.0, 500.0, wc);

    tree->scale(60.0, 150.0);
    tree->translate(300.0, 144.0, 500.0, wc);

    // Adicionando os party hats
    party_hat1->scale(16.0, 24.0);
    party_hat1->translate(300.0, 117.5 + 2.5, 400, wc);

    party_hat2->scale(16.0, 24.0);
    party_hat2->translate(325.0, 117.5 + 2.5, 600, wc);

    party_hat3->scale(16.0, 24.0);
    party_hat3->translate(580.0, 117.5 + 2.5, 400, wc);

    plate->scale(90.0, 5.0);
    plate->translate(450.0, 117.5 + 2.5, 500, wc);

    cake->scale(75.0, 40.0);
    cake->translate(450.0, 117.5 + 2.5 + 5.0, 500, wc);

    candle->scale(2.0, 14.0);
    candle->translate(450.0, 117.5 + 2.5 + 5.0 + 40.0 + 1.0, 500, wc);

    cherry1.scale(5);
    cherry1.translate(450.0, 117.5 + 2.5 + 5.0 + 40.0 + 1.0, 560, wc);

    cherry2.scale(5);
    cherry2.translate(450.0, 117.5 + 2.5 + 5.0 + 40.0 + 1.0, 440, wc);

    cherry3.scale(5);
    cherry3.translate(450.0 - 60, 117.5 + 2.5 + 5.0 + 40.0 + 1.0, 500, wc);

    cherry4.scale(5);
    cherry4.translate(450.0 + 60, 117.5 + 2.5 + 5.0 + 40.0 + 1.0, 500, wc);

    cherry5.scale(5);
    cherry5.translate(450.0 + 42.426, 117.5 + 2.5 + 5.0 + 40.0 + 1.0, 500 + 42.426, wc);

    cherry6.scale(5);
    cherry6.translate(450.0 - 42.426, 117.5 + 2.5 + 5.0 + 40.0 + 1.0, 500 + 42.426, wc);

    cherry7.scale(5);
    cherry7.translate(450.0 - 42.426, 117.5 + 2.5 + 5.0 + 40.0 + 1.0, 500 - 42.426, wc);

    cherry8.scale(5);
    cherry8.translate(450.0 + 42.426, 117.5 + 2.5 + 5.0 + 40.0 + 1.0, 500 - 42.426, wc);

    wallL.scale(10.0, 500.0, 1000.0);
    wallL.translate(0.0, 250.0, 500.0, wc);
    wallR.scale(10.0, 500.0, 1000.0);
    wallR.translate(1200.0, 250.0, 500.0, wc);
    ceiling.scale(1200.0, 10.0, 1000.0);
    ceiling.translate(600.0, 505.0, 500.0, wc);

    back_wall.scale(1200.0, 500.0, 10.0);
    back_wall.translate(600.0, 250.0, 0.0, wc);

    // Inserindo os objetos

    objects.push_back(std::make_shared<Mesh>(wallL));
    objects.push_back(std::make_shared<Mesh>(wallR));
    objects.push_back(std::make_shared<Mesh>(back_wall));
    objects.push_back(std::make_shared<Mesh>(ceiling));

    // objects.push_back(std::make_shared<Mesh>(roofL));
    // objects.push_back(std::make_shared<Mesh>(roofR));

    // objects.push_back(std::make_shared<Sphere>(ball));

    // objects.push_back(std::make_shared<Plane>(floor));

    objects.push_back(std::make_shared<Mesh>(table_supportL));
    objects.push_back(std::make_shared<Mesh>(table_supportL_back));
    objects.push_back(std::make_shared<Mesh>(table_supportR));
    objects.push_back(std::make_shared<Mesh>(table_supportR_back));
    objects.push_back(std::make_shared<Mesh>(table_lid));

    objects.push_back(party_hat1);
    objects.push_back(party_hat2);
    objects.push_back(party_hat3);

    objects.push_back(plate);
    objects.push_back(cake);
    objects.push_back(candle);
    objects.push_back(std::make_shared<Sphere>(cherry1));
    objects.push_back(std::make_shared<Sphere>(cherry2));
    objects.push_back(std::make_shared<Sphere>(cherry3));
    objects.push_back(std::make_shared<Sphere>(cherry4));
    objects.push_back(std::make_shared<Sphere>(cherry5));
    objects.push_back(std::make_shared<Sphere>(cherry6));
    objects.push_back(std::make_shared<Sphere>(cherry7));
    objects.push_back(std::make_shared<Sphere>(cherry8));

    // objects.push_back(woodBase);
    // objects.push_back(wood);
    // objects.push_back(tree);

    lightSources.push_back(
        std::make_shared<Point>(Point(I_F_1, P_F_1.head<3>())));
    lightSources.push_back(std::make_shared<Ambient>(Ambient(I_A)));
    /*lightSources.push_back(
        std::make_shared<Directional>(Directional(I_F_2, D_F_2)));*/
    // lightSources.push_back(std::make_shared<Point>(Point(I_F_1, P_F_2)));
    /*lightSources.push_back(
        std::make_shared<Spot>(Spot(I_F_3, P_I_3, P_S_3, 12.0)));*/
    /*lightSources.push_back(
        std::make_shared<Spot>(Spot(I_F_3, P_I_3, P_S_4, 12.0)));*/

    std::shared_ptr<Object> pickedObj = nullptr;
    std::shared_ptr<Scene> scene = std::make_shared<Scene>(Scene(viewport, camera, lightSources, objects, isPerspective));
    Canvas canvas(canvasWidth, canvasHeight, -dWindow, scene);

    canvas.init();
    canvas.update();

    std::thread inputThread([&]() {
        int selected;
        while (true) {
            std::cout << "1 - Translate " << std::endl;
            std::cout << "2 - Scale " << std::endl;
            std::cout << "3 - Rotate " << std::endl;
            std::cout << "4 - Shear " << std::endl;
            std::cout << "5 - Mirroring " << std::endl;
            std::cout << "6 - Modify Material " << std::endl;
            std::cout << "7 - Reposition Camera " << std::endl;
            std::cout << "8 - Manage Light Sources " << std::endl;
            std::cout << "9 - Switch Camera Projection" << std::endl;

            std::cin >> selected;
            Eigen::Matrix4d m;

            if (pickedObj == nullptr && selected >= 1 && selected <= 6) {
                std::cout << "No selected object" << std::endl;
                continue;
            }

            switch (selected) {
                case 1: {
                    double x, y, z;
                    std::cout << "Set coordinates (X,Y,Z): ";
                    std::cin >> x;
                    std::cin >> y;
                    std::cin >> z;

                    pickedObj->returnToWorld(cw, false);
                    pickedObj->translate(x, y, z, wc);
                    canvas.update();
                    break;
                }
                case 2: {
                    double x = 0.0, y = x, z = x;

                    if (pickedObj->getType() == utilsStructs::OBJ_TYPE::CONE) {
                        std::cout << "Set scale (Radius, Height): ";
                        std::cin >> x;
                        std::cin >> y;
                    }
                    if (pickedObj->getType() == utilsStructs::OBJ_TYPE::CYLINDER) {
                        std::cout << "Set scale (Radius, Height): ";
                        std::cin >> x;
                        std::cin >> y;
                    }
                    if (pickedObj->getType() == utilsStructs::OBJ_TYPE::MESH) {
                        std::cout << "Set scale (X,Y,Z): ";
                        std::cin >> x;
                        std::cin >> y;
                        std::cin >> z;
                    }
                    if (pickedObj->getType() == utilsStructs::OBJ_TYPE::PLANE) {
                        std::cout << "Invalid transformation for plane" << std::endl;
                        break;
                    }
                    if (pickedObj->getType() == utilsStructs::OBJ_TYPE::SPHERE) {
                        std::cout << "Set scale: ";
                        std::cin >> x;
                    }

                    pickedObj->returnToWorld(cw, false);

                    pickedObj->scale(x, y, z);

                    std::tuple<double, double, double> coordinates = pickedObj->getCoordinates();
                    pickedObj->translate(get<0>(coordinates), get<1>(coordinates), get<2>(coordinates), wc);

                    canvas.update();
                    break;
                }

                case 3: {
                    double angle;
                    int axis;

                    std::cout << "Rotating Angle: ";
                    std::cin >> angle;
                    std::cout << "Select Axis: ";
                    std::cout << "0 - X" << std::endl;
                    std::cout << "1 - Y" << std::endl;
                    std::cout << "2 - Z" << std::endl;
                    std::cin >> axis;

                    matrix::AXIS axisEnum = static_cast<matrix::AXIS>(axis);

                    pickedObj->returnToWorld(cw, false);

                    pickedObj->rotate(angle, axisEnum);

                    std::tuple<double, double, double> coordinates = pickedObj->getCoordinates();
                    std::cout << get<0>(coordinates) << " " << get<1>(coordinates) << " " << get<2>(coordinates) << "\n";
                    pickedObj->translate(get<0>(coordinates), get<1>(coordinates), get<2>(coordinates), wc);
                    canvas.update();
                    break;
                }

                case 4:
                    if (pickedObj->getType() == utilsStructs::OBJ_TYPE::MESH) {
                        double angle;
                        int axis;

                        std::cout << "Shearing Angle: ";
                        std::cin >> angle;
                        std::cout << "Select Axis: ";
                        std::cout << "0 - XY" << std::endl;
                        std::cout << "1 - XZ" << std::endl;
                        std::cout << "2 - YX" << std::endl;
                        std::cout << "3 - YZ" << std::endl;
                        std::cout << "4 - ZX" << std::endl;
                        std::cout << "5 - ZY" << std::endl;
                        std::cin >> axis;

                        matrix::SHEAR_AXIS axisEnum = static_cast<matrix::SHEAR_AXIS>(axis);

                        pickedObj->returnToWorld(cw, false);

                        pickedObj->shear(angle, axisEnum);

                        std::tuple<double, double, double> coordinates = pickedObj->getCoordinates();
                        pickedObj->translate(get<0>(coordinates), get<1>(coordinates), get<2>(coordinates), wc);
                        canvas.update();
                        break;
                    }
                case 5: {
                    int axis;
                    std::cout << "Select Axis: " << std::endl;
                    std::cout << "0 - XY" << std::endl;
                    std::cout << "1 - XZ" << std::endl;
                    std::cout << "2 - YZ" << std::endl;
                    std::cin >> axis;

                    matrix::REFLECTION_AXIS axisEnum = static_cast<matrix::REFLECTION_AXIS>(axis);
                    pickedObj->returnToWorld(cw, true);
                    pickedObj->reflection(axisEnum, scene->objects, wc);
                    pickedObj->backToCamera(wc);
                    canvas.update();
                    break;
                }

                case 6: {
                    int matOption;
                    double p1, p2, p3;

                    std::cout << "Modify Material" << std::endl;
                    std::cout << "1 - Ambient" << std::endl;
                    std::cout << "2 - Difuse" << std::endl;
                    std::cout << "3 - Specular" << std::endl;
                    std::cout << "4 - All" << std::endl;
                    std::cin >> matOption;
                    std::cout << "Enter new properties (0 to 1): (p1, p2, p3): " << std::endl;
                    std::cin >> p1;
                    std::cin >> p2;
                    std::cin >> p3;

                    pickedObj->modifyK(Eigen::Vector3d(p1, p2, p3), matOption);
                    canvas.update();
                    break;
                }

                case 7:
                    int option;
                    std::cout << "Modify Camera Parameters" << std::endl;
                    std::cout << "1 - Eye Position (O)" << std::endl;
                    std::cout << "2 - Look At Point" << std::endl;
                    std::cout << "3 - View Up Point (up)" << std::endl;
                    std::cout << "4 - Resize Viewport" << std::endl;
                    std::cout << "5 - Focal Length (D)" << std::endl;
                    std::cin >> option;

                    switch (option) {
                        case 1: {
                            double x, y, z;
                            std::cout << "Insert new coordinates (x, y, z): " << std::endl;
                            std::cin >> x;
                            std::cin >> y;
                            std::cin >> z;

                            O(0) = x;
                            O(1) = y;
                            O(2) = z;

                            wc = matrix::lookAt(O.head<3>(), at, up);
                            cw = matrix::cwMatrix(O.head<3>(), at, up);
                            O = wc * O;
                            scene->setOrigin(x, y, z);

                            // Provavelmente não está funcionando porque o wc não está sendo multiplicado corretamente
                            for (std::shared_ptr<Object> obj : scene->objects) {
                                std::tuple<double, double, double> coordinates = obj->getCoordinates();
                                Eigen::Vector4d newCoordinates(get<0>(coordinates), get<1>(coordinates), get<2>(coordinates), 1.0);
                                std::cout << newCoordinates(0) << " " << newCoordinates(1) << " " << newCoordinates(2) << "\n";
                                newCoordinates = cw * newCoordinates;
                                obj->translate(newCoordinates(0), newCoordinates(1), newCoordinates(2), wc);
                            }

                            // for (std::shared_ptr<LightSource> lightSource : scene->lightSources) {
                            //     lightSource->translate(x, y, z, wc);
                            // }

                            canvas.update();

                            break;
                        }
                        case 2: {
                            break;
                        }
                        case 3: {
                            break;
                        }
                        case 4: {
                            double w, h;
                            std::cout << "Insert new dimensions (width, height): " << std::endl;
                            std::cin >> w;
                            std::cin >> h;
                            scene->resizeViewport(w, h);
                            canvas.update();
                            break;
                        }
                        case 5: {
                            break;
                        }

                        default:
                            break;
                    }

                    break;
                case 8:
                    break;
                case 9: {
                    scene->switchProjection();
                    std::string projection = scene->getProjection() ? "Perspective" : "Ortogonal";
                    canvas.update();
                    std::cout << "Projection changed to: " << projection << std::endl;
                    break;
                }

                default:
                    std::cout << "Invalid Option" << std::endl;
                    break;
            }
            // system("clear");
        }
    });
    canvas.eventLoop(pickedObj);
    return 0;
}
