#include "scene.h"

#include <chrono>
#include <iostream>

#include "utils.h"

std::vector<unsigned char> Scene::display() {
  double deltaX = viewport.width / viewport.nColumns;
  double deltaY = viewport.height / viewport.nRows;
  double x, y;
  std::vector<unsigned char> pixelVector;
  Eigen::Vector3d D(0, 0, 0);

  auto start = std::chrono::steady_clock::now();
  for (int r = 0; r < viewport.nRows; r++) {
    y = (viewport.height / 2) - (deltaY / 2) - (r * deltaY);
    for (int c = 0; c < viewport.nColumns; c++) {
      x = -(viewport.width / 2) + (deltaX / 2) + (c * deltaX);
      // D(0) = x - x;
      // D(1) = y - y;
      D(0) = x - camera.O(0);
      D(1) = camera.O(1) - y;
      D(2) = -viewport.dWindow;

      // displayStructs::Camera cameraTest(Eigen::Vector3d(x, y, 0),
      // camera.I_A);

      utilsStructs::Color color =
          utils::traceRay(camera, D, lightSources, objects, int(x), int(y));

      pixelVector.push_back(color.R);
      pixelVector.push_back(color.G);
      pixelVector.push_back(color.B);
    }
  }
  std::cout << "Elapsed(ms)="
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::steady_clock::now() - start)
                       .count() /
                   1000.0
            << std::endl;
  return pixelVector;
}