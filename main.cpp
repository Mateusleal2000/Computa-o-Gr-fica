#define _USE_MATH_DEFINES

#include <GL/glut.h>
#include <Magick++.h>

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
#include "textureUtils.h"
#include "utils.h"
#include "utilsStructs.h"

double canvasWidth = 500;
double canvasHeight = 500;
unsigned char* pixelArray;

void draw() {
  glDrawPixels(canvasHeight, canvasWidth, GL_RGB, GL_UNSIGNED_BYTE, pixelArray);
  glutSwapBuffers();
}

int main(int argc, char** argv) {
  Magick::InitializeMagick(*argv);
  double radius = 5;
  double dWindow = 25;
  double x = 0;
  double y = 0;
  double z = -(dWindow + radius);
  double viewPortWidth = 60;
  double viewPortHeight = 60;
  double nRow = 500;
  double nCol = 500;

  Eigen::Vector3d O(0.0, 0.0, 0.0);
  Eigen::Vector3d center(x, y, z);
  double I_A = 0.3;

  Eigen::Vector3d I_F_1(0.7, 0.7, 0.7);
  // Eigen::Vector3d P_F_1(0, 200, -150);
  Eigen::Vector3d P_F_1(-100, 140, -20);
  Eigen::Vector3d P_F_2(100, 200, -20);

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

  // floor plane
  Eigen::Vector3d Ke_2(0.0, 0.0, 0.0);
  Eigen::Vector3d Ka_2(0.7, 0.2, 0.2);
  Eigen::Vector3d Kd_2(0.7, 0.2, 0.2);

  // background plane
  Eigen::Vector3d Ke_3(0.686, 0.933, 0.933);
  Eigen::Vector3d Ka_3(0.686, 0.933, 0.933);
  Eigen::Vector3d Kd_3(0.686, 0.933, 0.933);

  // cilinder
  Eigen::Vector3d Ke_4(0.933, 0.933, 0.933);
  Eigen::Vector3d Ka_4(0.933, 0.933, 0.933);
  Eigen::Vector3d Kd_4(0.933, 0.933, 0.933);

  // cone
  Eigen::Vector3d Ke_5(0.824, 0.706, 0.549);
  Eigen::Vector3d Ka_5(0.824, 0.706, 0.549);
  Eigen::Vector3d Kd_5(0.824, 0.706, 0.549);

  Eigen::Vector3d Ke_6(0.0, 1.0, 0.498);
  Eigen::Vector3d Ka_6(0.0, 1.0, 0.498);
  Eigen::Vector3d Kd_6(0.0, 1.0, 0.498);

  Eigen::Vector3d Ke_7(1.0, 0.078, 0.576);
  Eigen::Vector3d Ka_7(1.0, 0.078, 0.576);
  Eigen::Vector3d Kd_7(1.0, 0.078, 0.576);

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
  double height_2 = radius / 3;

  utilsStructs::materialK K_1(Ke_1, Ka_1, Kd_1);
  utilsStructs::materialK K_2(Ke_2, Ka_2, Kd_2);
  utilsStructs::materialK K_3(Ke_3, Ka_3, Kd_3);
  utilsStructs::materialK K_4(Ke_4, Ka_4, Kd_4);
  utilsStructs::materialK K_5(Ke_5, Ka_5, Kd_5);
  utilsStructs::materialK K_6(Ke_6, Ka_6, Kd_6);
  utilsStructs::materialK K_7(Ke_7, Ka_7, Kd_7);

  displayStructs::Viewport viewport(viewPortWidth, viewPortHeight, nRow, nCol,
                                    dWindow);

  displayStructs::Camera camera(O);

  std::vector<std::shared_ptr<LightSource>> lightSources;
  std::vector<std::shared_ptr<Object>> objects;

  // Eigen::Vector3d center1(0, 95, -200);
  //Eigen::Vector3d center1(0, 0, -120);
  Eigen::Vector3d center1(0, 0, 0);
  Eigen::Vector3d center2(0, -150, -200);
  Eigen::Vector3d center3(0, -60, -200);
  Eigen::Vector3d center4(0, 20, -150);

  double m_1 = 10;
  double m_2 = 1;
  double m_3 = 1;

  Mesh cube(K_7, m_1, "magic_cube.obj");

  cube.scale(60.0, 20.0, 20.0);

  // cube.rotate(45.0, matrix::AXIS::Y);

  cube.shear(40.0, matrix::SHEAR_AXIS::XY);

  cube.translate(-20.0, -130.0, -165.0);

  //Mesh reflectedCube = cube.reflection(matrix::REFLECTION_AXIS::XZ);

  /*objects.push_back(
      std::make_shared<Sphere>(Sphere(K_1, m_1, radius, center1)));

  objects.push_back(std::make_shared<Plane>(Plane(
      K_2, m_2, Eigen::Vector3d(0, -radius, 0), Eigen::Vector3d(0, 1, 0))));

  objects.push_back(std::make_shared<Plane>(
      Plane(K_3, m_3, Eigen::Vector3d(0, 0, -300), Eigen::Vector3d(0, 0, 1))));

  objects.push_back(std::make_shared<Cylinder>(
      Cylinder(K_4, m_1, radius/3, center1, height_1, dCil_1.normalized())));

  objects.push_back(std::make_shared<Cone>(
      Cone(K_5, m_1, radius * 1.5, center1 + (dCil_1.normalized() * height_1),
           height_2,
     dCone_2.normalized())));*/

  // bolinha da árvore de natal
  //objects.push_back(std::make_shared<Sphere>(Sphere(K_1, m_1, radius, center1)));
  //0, 0, -120
  Sphere bolinha1(K_1, m_1, radius, center1);
  bolinha1.scale(4.0);
  bolinha1.translate(0, 0, -120);
  Sphere bolinha2 = bolinha1.reflection(matrix::REFLECTION_AXIS::YZ);
  objects.push_back(std::make_shared<Sphere>(bolinha1));
  objects.push_back(std::make_shared<Sphere>(bolinha2));

  // chão O K vai ser uma textura de madeira
  objects.push_back(std::make_shared<Plane>(
      Plane(K_3, m_2, Eigen::Vector3d(0, -150, 0), Eigen::Vector3d(0, 1, 0),
            "wood.png", textureUtils::REPEAT)));

  // parede lateral direita
  objects.push_back(std::make_shared<Plane>(Plane(
      K_3, m_2, Eigen::Vector3d(200, -150, 0), Eigen::Vector3d(-1, 0, 0))));

  // parede lateral esquerda
  objects.push_back(std::make_shared<Plane>(Plane(
      K_3, m_2, Eigen::Vector3d(-200, -150, 0), Eigen::Vector3d(1, 0, 0))));

  // parede frontal
  objects.push_back(std::make_shared<Plane>(Plane(
      K_3, m_2, Eigen::Vector3d(200, -150, -400), Eigen::Vector3d(0, 0, 1))));

  // parede teto
  objects.push_back(std::make_shared<Plane>(
      Plane(K_4, m_2, Eigen::Vector3d(0, 150, 0), Eigen::Vector3d(0, -1, 0))));

  // tronco da árvore-cilindro
  /*objects.push_back(std::make_shared<Cylinder>(
      Cylinder(K_5, m_1, 5.0, center2, 90.0, dCil_3.normalized())));*/

  // conífera-cone
  /*objects.push_back(std::make_shared<Cone>(
      Cone(K_6, m_1, 90, center3, 150.0, dCone_3.normalized())));*/

  // Eigen::Matrix4d m = meshMatrix::scale(3.0, 3.0, 3.0);
  // applyMatrix(m);
  //  presente
  //objects.push_back(std::make_shared<Mesh>(cube));
  //objects.push_back(std::make_shared<Mesh>(reflectedCube));

  lightSources.push_back(std::make_shared<Point>(Point(I_F_1, P_F_1)));
  /*lightSources.push_back(
      std::make_shared<Directional>(Directional(I_F_2, D_F_2)));*/
  // lightSources.push_back(std::make_shared<Point>(Point(I_F_1, P_F_2)));
  /*lightSources.push_back(
      std::make_shared<Spot>(Spot(I_F_3, P_I_3, P_S_3, 12.0)));*/
  /*lightSources.push_back(
      std::make_shared<Spot>(Spot(I_F_3, P_I_3, P_S_4, 12.0)));*/
  lightSources.push_back(std::make_shared<Ambient>(Ambient(I_A)));

  Scene scene(viewport, camera, lightSources, objects);

  std::vector<unsigned char> pixelVector = scene.display();

  pixelArray = pixelVector.data();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(canvasHeight, canvasWidth);
  glutCreateWindow("Cena");

  glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

  glutDisplayFunc(draw);
  glutIdleFunc(draw);

  glutMainLoop();
  return 0;
}