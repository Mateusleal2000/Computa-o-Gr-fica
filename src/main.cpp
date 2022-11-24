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
    double x = 0;
    double y = 0;
    double z = -(dWindow + radius);

    bool isPerspective = true;
    double canvasWidth = 500;
    double canvasHeight = 500;
    double viewPortWidth = isPerspective ? 60 : 1500;
    double viewPortHeight = isPerspective ? 60 : 1500;
    double nRow = 500;
    double nCol = 500;

    double lx = 300.0;
    double ly = 400.0;
    double lz = 1500.0;

    double I_A = 0.3;

    Eigen::Vector4d O(lx, ly, lz, 1.0);
    Eigen::Vector3d at(300.0, 97.5, 500.0);
    // Eigen::Vector3d at(lx, ly, 1.0);
    Eigen::Vector3d up(lx, ly + 100.0, lz);
    Eigen::Matrix4d wc = matrix::lookAt(O.head<3>(), at, up);
    Eigen::Matrix4d cw = matrix::cwMatrix(O.head<3>(), at, up);
    // std::cout << up - O.head<3>() << "\n";
    O = wc * O;
    Eigen::Vector3d center(x, y, z);

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

    utilsStructs::materialK lid_K(lid_Ke, lid_Ka, lid_Kd);
    utilsStructs::materialK support_K(support_Ke, support_Ka, support_Kd);

    displayStructs::Viewport viewport(viewPortWidth, viewPortHeight, nRow, nCol,
                                      dWindow);

    displayStructs::Camera camera(O.head<3>());

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
    // std::string catPath = "cat.obj";

    // Gato
    // Mesh cat(lid_K, m_1, catPath);

    // Mesa
    Mesh table_lid(lid_K, m_1, cubePath);
    Mesh table_supportL(support_K, m_1, cubePath);
    Mesh table_supportR(support_K, m_1, cubePath);

    // Galp�o frente
    Mesh beamL(K_4, m_1, cubePath);
    Mesh support_columnL(K_4, m_1, cubePath);
    Mesh beamR(K_4, m_1, cubePath);
    Mesh support_columnR(K_4, m_1, cubePath);

    // Galp�o tr�s
    Mesh back_beamL(K_4, m_1, cubePath);
    Mesh back_support_columnL(K_4, m_1, cubePath);
    Mesh back_beamR(K_4, m_1, cubePath);
    Mesh back_support_columnR(K_4, m_1, cubePath);

    // Galp�o paredes
    Mesh wallL(K_2, m_1, cubePath);
    Mesh wallR(K_2, m_1, cubePath);
    Mesh back_wall(K_2, m_1, cubePath);

    // Telhado
    Mesh roofR(K_6, m_1, cubePath);
    Mesh roofL(K_6, m_1, cubePath);

    //�rvore
    Sphere ball(K_1, m_1, radius, center1);
    auto woodBase = std::make_shared<Cylinder>(
        Cylinder(K_4, m_1, 1, center1, 1, dCil_3.normalized()));
    auto wood = std::make_shared<Cylinder>(
        Cylinder(K_4, m_1, 1, center1, 1, dCil_3.normalized()));
    auto tree = std::make_shared<Cone>(
        Cone(K_5, m_1, 1, center1, 1, dCil_3.normalized()));

    // Ch�o
    Eigen::Vector4d floor_pos(0.0, 0.0, 0.0, 1);
    Eigen::Vector4d floor_dir(0.0, 1.0, 0.0, 0.0);
    Plane floor(K_3, m_2, (wc * floor_pos).head<3>(),
                ((wc * floor_dir).head<3>()).normalized());

    // Posicionando mesa
    table_supportL.scale(5.0, 95.0, 150.0);
    table_supportL.translate(175.0, 42.5, 500.0, wc);

    table_supportR.scale(5.0, 95.0, 150.0);
    table_supportR.translate(425.0, 42.5, 500.0, wc);

    table_lid.scale(250.0, 5.0, 150.0);
    table_lid.translate(300.0, 95.0, 500.0, wc);

    // Posicionando �rvore
    ball.scale(4.5);
    ball.translate(300.0, 294.0, 500.0, wc);

    woodBase->scale(30.0, 9.0);
    woodBase->translate(300.0, 95.0, 500.0, wc);

    wood->scale(6.0, 40.0);
    wood->translate(300.0, 104.0, 500.0, wc);

    tree->scale(60.0, 150.0);
    tree->translate(300.0, 144.0, 500.0, wc);

    // Posicionando galp�o

    // Vigas
    beamL.scale(300.0, 50.0, 30.0);
    beamL.shear(37, matrix::SHEAR_AXIS::XY);
    beamL.translate(150, 570.0, 1000.0, wc);

    beamR.scale(300.0, 50.0, 30.0);
    beamR.shear(-37, matrix::SHEAR_AXIS::XY);
    beamR.translate(450.0, 570.0, 1000.0, wc);

    // Colunas de suporte
    support_columnL.scale(50.0, 500.0, 30.0);
    support_columnL.translate(0.0, 250.0, 1000.0, wc);

    support_columnR.scale(50.0, 500.0, 30.0);
    support_columnR.translate(600.0, 250.0, 1000.0, wc);

    // Vigas de tr�s
    back_beamL.scale(300.0, 50.0, 30.0);
    back_beamL.shear(37.0, matrix::SHEAR_AXIS::XY);
    back_beamL.translate(150, 570.0, 0.0, wc);

    back_beamR.scale(300.0, 50.0, 30.0);
    back_beamR.shear(-37.0, matrix::SHEAR_AXIS::XY);
    back_beamR.translate(450.0, 570.0, 0.0, wc);

    // Colunas de tr�s
    back_support_columnL.scale(50.0, 500.0, 30.0);
    back_support_columnL.translate(0.0, 250.0, 0.0, wc);

    back_support_columnR.scale(50.0, 500.0, 30.0);
    back_support_columnR.translate(600.0, 250.0, 0.0, wc);

    wallL.scale(10.0, 500.0, 1000.0);
    wallL.translate(0.0, 250.0, 500.0, wc);
    wallR.scale(10.0, 500.0, 1000.0);
    wallR.translate(600.0, 250.0, 500.0, wc);

    back_wall.scale(600.0, 500.0, 10.0);
    back_wall.translate(300.0, 250.0, 0.0, wc);

    // Posicionando telhados
    roofL.scale(394.73, 20.0, 1000.0);
    roofL.rotate(37, matrix::AXIS::Z);
    roofL.translate(150.0, 570.0, 500.0, wc);

    roofR.scale(394.73, 20.0, 1000.0);
    roofR.rotate(-37, matrix::AXIS::Z);
    roofR.translate(450.0, 570.0, 500.0, wc);

    // Inserindo os objetos

    /*cat.scale(100.0, 100.0, 100.0);
    cat.translate(450.0, 570.0, 500.0, wc);
    objects.push_back(std::make_shared<Mesh>(cat));*/

    // objects.push_back(std::make_shared<Mesh>(support_columnL));
    // objects.push_back(std::make_shared<Mesh>(support_columnR));
    // objects.push_back(std::make_shared<Mesh>(beamL));
    // objects.push_back(std::make_shared<Mesh>(beamR));

    // objects.push_back(std::make_shared<Mesh>(back_beamR));
    // objects.push_back(std::make_shared<Mesh>(back_beamL));
    // objects.push_back(std::make_shared<Mesh>(back_support_columnL));
    // objects.push_back(std::make_shared<Mesh>(back_support_columnR));

    objects.push_back(std::make_shared<Mesh>(wallL));
    // objects.push_back(std::make_shared<Mesh>(wallR));
    // objects.push_back(std::make_shared<Mesh>(back_wall));

    // objects.push_back(std::make_shared<Mesh>(roofL));
    // objects.push_back(std::make_shared<Mesh>(roofR));

    // objects.push_back(std::make_shared<Sphere>(ball));

    objects.push_back(std::make_shared<Plane>(floor));

    // objects.push_back(std::make_shared<Mesh>(table_supportL));
    // objects.push_back(std::make_shared<Mesh>(table_supportR));
    // objects.push_back(std::make_shared<Mesh>(table_lid));
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

                    pickedObj->returnToWorld(cw);
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

                    pickedObj->returnToWorld(cw);

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

                    pickedObj->returnToWorld(cw);

                    pickedObj->rotate(angle, axisEnum);

                    std::tuple<double, double, double> coordinates = pickedObj->getCoordinates();
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

                        pickedObj->returnToWorld(cw);

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
                    // pickedObj->returnToWorld(cw);
                    pickedObj->reflection(axisEnum, scene->objects);
                    // std::tuple<double, double, double> coordinates = pickedObj->getCoordinates();
                    // pickedObj->translate(get<0>(coordinates), get<1>(coordinates), get<2>(coordinates), wc);
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
                    std::cout << "Enter new properties (0 to 1): (p1, p2, p3) " << std::endl;
                    std::cin >> p1;
                    std::cin >> p2;
                    std::cin >> p3;

                    pickedObj->modifyK(Eigen::Vector3d(p1, p2, p3), matOption);
                    canvas.update();
                    break;
                }

                case 7:
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
