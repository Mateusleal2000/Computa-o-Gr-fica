#define _USE_MATH_DEFINES

#include <GL/glut.h>

#include <Eigen/Dense>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include "ambient.h"
#include "cone.h"
#include "cylinder.h"
#include "directional.h"
#include "display.h"
#include "displayStructs.h"
#include "lightSource.h"
#include "matrix.h"
#include "mesh.h"
#include "plane.h"
#include "point.h"
#include "scene.h"
#include "sphere.h"
#include "spot.h"
#include "utils.h"
#include "utilsStructs.h"

int xj;
int yj;
bool isPerspective = true;
double canvasWidth = 500;
double canvasHeight = 500;
double viewPortWidth = isPerspective ? 60 : 2000;
double viewPortHeight = isPerspective ? 60 : 2000;
double nRow = 500;
double nCol = 500;
unsigned char* pixelArray;

void draw() {
  glDrawPixels(canvasHeight, canvasWidth, GL_RGB, GL_UNSIGNED_BYTE, pixelArray);
  glutSwapBuffers();
}

void onClick(int button, int state, int x, int y) {
  double deltaX = viewPortWidth / nCol;
  double deltaY = viewPortHeight / nRow;

  xj = (viewPortHeight / 2.0) + (deltaX / 2.0) + x * deltaX;
  yj = -(viewPortWidth / 2.0) + (deltaY / 2.0) + y * deltaY;

  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    std::cout << xj << " " << yj << " "
              << "\n";
    // glutDisplayFunc(draw);
    glutPostRedisplay();
  }
}

int main(int argc, char** argv) {
  double radius = 1.0;
  double dWindow = 25;
  double x = 0;
  double y = 0;
  double z = -(dWindow + radius);

  double lx = -600.0;
  double ly = 300.0;
  double lz = 500.0;

  double I_A = 0.3;

  Eigen::Vector4d O(lx, ly, lz, 1.0);
  Eigen::Vector3d at(300.0, 97.5, 500.0);
  // Eigen::Vector3d at(lx, ly, 1.0);
  Eigen::Vector3d up(lx, ly + 100.0, lz);
  Eigen::Matrix4d wc = matrix::lookAt(O.head<3>(), at, up);
  // std::cout << up - O.head<3>() << "\n";
  O = wc * O;
  Eigen::Vector3d center(x, y, z);

  Eigen::Vector3d I_F_1(0.7, 0.7, 0.7);
  Eigen::Vector4d P_F_1(300.0, 100.0, 1200.0, 1.0);
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

  std::string cubePath = "magic_cube.obj";
  std::string catPath = "gato.obj";

  //Gato
  //Mesh cat(lid_K, m_1, catPath);

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

  objects.push_back(std::make_shared<Mesh>(support_columnL));
  objects.push_back(std::make_shared<Mesh>(support_columnR));
  objects.push_back(std::make_shared<Mesh>(beamL));
  objects.push_back(std::make_shared<Mesh>(beamR));

  objects.push_back(std::make_shared<Mesh>(back_beamR));
  objects.push_back(std::make_shared<Mesh>(back_beamL));
  objects.push_back(std::make_shared<Mesh>(back_support_columnL));
  objects.push_back(std::make_shared<Mesh>(back_support_columnR));

  objects.push_back(std::make_shared<Mesh>(wallL));
  objects.push_back(std::make_shared<Mesh>(wallR));
  objects.push_back(std::make_shared<Mesh>(back_wall));

  objects.push_back(std::make_shared<Mesh>(roofL));
  objects.push_back(std::make_shared<Mesh>(roofR));

  objects.push_back(std::make_shared<Sphere>(ball));

  objects.push_back(std::make_shared<Plane>(floor));

  objects.push_back(std::make_shared<Mesh>(table_supportL));
  objects.push_back(std::make_shared<Mesh>(table_supportR));
  objects.push_back(std::make_shared<Mesh>(table_lid));
  objects.push_back(woodBase);
  objects.push_back(wood);
  objects.push_back(tree);

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


  Scene scene(viewport, camera, lightSources, objects);

  std::vector<unsigned char> pixelVector = scene.display(isPerspective);
  std::reverse(pixelVector.begin(), pixelVector.end());

  pixelArray = pixelVector.data();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(canvasHeight, canvasWidth);
  glutCreateWindow("Cena");

  glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

  glutDisplayFunc(draw);
  glutMouseFunc(onClick);
  glutIdleFunc(draw);
  glutMainLoop();

  return 0;
}