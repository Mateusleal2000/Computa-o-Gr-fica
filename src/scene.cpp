#include "scene.h"

#include <chrono>
#include <iostream>

#include "utils.h"

std::vector<unsigned char> Scene::display(bool isPerspective) {
    double deltaX = viewport.width / viewport.nColumns;
    double deltaY = viewport.height / viewport.nRows;
    double x, y;
    std::vector<unsigned char> pixelVector;
    Eigen::Vector3d D(0, 0, 0);
    Eigen::Vector3d orthDir(0, 0, -1);

    auto start = std::chrono::steady_clock::now();
    for (int r = 0; r < viewport.nRows; r++) {
        y = (viewport.height / 2) - (deltaY / 2) - (r * deltaY);
        for (int c = 0; c < viewport.nColumns; c++) {
            x = -(viewport.width / 2) + (deltaX / 2) + (c * deltaX);

            D(0) = x - camera.O(0);
            D(1) = y - camera.O(1);
            D(2) = -viewport.dWindow;

            utilsStructs::Color color(0);

            if (isPerspective) {
                color =
                    utils::traceRay(camera, D, lightSources, objects, int(x), int(y));
            } else {
                color =
                    utils::traceRay(D, orthDir, lightSources, objects, int(x), int(y));
            }

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

std::shared_ptr<Object> Scene::pick(Eigen::Vector3d O, Eigen::Vector3d D, std::vector<std::shared_ptr<Object>> objects) {
    double inf = INFINITY;
    // double t;
    // std::shared_ptr<Object> closestObject = nullptr;

    auto [closestT, closestObject] = utils::closestIntersection(O, D, 0, inf, objects);
    if (closestT == INFINITY) {
        closestObject = nullptr;
    }
    return closestObject;
}

std::vector<std::shared_ptr<Object>> Scene::getObjects() {
    return this->objects;
}