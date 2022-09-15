#include <GL/glut.h>

#include <Eigen/Dense>
#include <iostream>
#include <memory>
#include <vector>

#include "display.h"
#include "displayStructs.h"
#include "plane.h"
#include "sphere.h"
#include "utils.h"
#include "utilsStructs.h"
#include "scene.h"

double canvasWidth = 500;
double canvasHeight = 500;
unsigned char* pixelArray;

void draw() {
  glDrawPixels(canvasHeight, canvasWidth, GL_RGB, GL_UNSIGNED_BYTE, pixelArray);
  glutSwapBuffers();
}

int main(int argc, char** argv) {
  double radius = 40;
  double dWindow = 30;
  double x = 0;
  double y = 0;
  double z = -(dWindow + radius);
  double viewPortWidth = 60;
  double viewPortHeight = 60;
  double nRow = 500;
  double nCol = 500;

  Eigen::Vector3d O(0.0, 0.0, 0.0);
  Eigen::Vector3d center(x, y, z);
  Eigen::Vector3d I_A(0.3, 0.3, 0.3);

  Eigen::Vector3d I_F_1(0.7, 0.7, 0.7);
  Eigen::Vector3d P_F_1(0, 60, -30);

  Eigen::Vector3d I_F_2(1.0, 1.0, 1.0);
  Eigen::Vector3d P_F_2(0, 120, -30);

  Eigen::Vector3d Ke_1(0.7, 0.2, 0.2);
  Eigen::Vector3d Ka_1(0.7, 0.2, 0.2);
  Eigen::Vector3d Kd_1(0.7, 0.2, 0.2);

  Eigen::Vector3d Ke_2(0.0, 0.0, 0.0);
  Eigen::Vector3d Ka_2(0.7, 0.2, 0.2);
  Eigen::Vector3d Kd_2(0.7, 0.2, 0.2);

  Eigen::Vector3d Ke_3(0.0, 0.0, 0.0);
  Eigen::Vector3d Ka_3(0.3, 0.3, 0.7);
  Eigen::Vector3d Kd_3(0.3, 0.3, 0.7);

  utilsStructs::materialK K_1(Ke_1, Ka_1, Kd_1);
  utilsStructs::materialK K_2(Ke_2, Ka_2, Kd_2);
  utilsStructs::materialK K_3(Ke_3, Ka_3, Kd_3);

  displayStructs::Viewport viewport(viewPortWidth, viewPortHeight, nRow, nCol,
                                    dWindow);
  displayStructs::LightSource lS_1(I_F_1, P_F_1);
  displayStructs::LightSource lS_2(I_F_2, P_F_2);
  displayStructs::Camera camera(O, I_A);

  std::vector<std::shared_ptr<displayStructs::LightSource>> lightSources;
  std::vector<std::shared_ptr<Object>> objects;

  Eigen::Vector3d center1(0, 0, -100);
  Eigen::Vector3d center2(0.6, -0.4, z);
  Eigen::Vector3d center3(-0.6, -0.4, z);

  double m_1 = 10;
  double m_2 = 1;
  double m_3 = 1;

  // objetos válidos
  objects.push_back(std::make_shared<Sphere>(
      Sphere(utilsStructs::Color(255, 0, 0), K_1, m_1, radius, center1)));
  objects.push_back(std::make_shared<Plane>(
      Plane(utilsStructs::Color(100), K_2, m_2, Eigen::Vector3d(0, -radius, 0),
            Eigen::Vector3d(0, 1, 0))));
  objects.push_back(std::make_shared<Plane>(
      Plane(utilsStructs::Color(100), K_3, m_3,
            Eigen::Vector3d(0, 0, -200), Eigen::Vector3d(0, 0, 1))));

  lightSources.push_back(std::make_shared<displayStructs::LightSource>(lS_1));
  lightSources.push_back(std::make_shared<displayStructs::LightSource>(lS_2));

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