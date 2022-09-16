#include "utils.h"

#include <iostream>

namespace utils {
double inf = std::numeric_limits<double>::infinity();
int BACKGROUND_COLOR = 100;

std::tuple<double, std::shared_ptr<Object>> closestIntersection(
    Eigen::Vector3d O, Eigen::Vector3d D, double tMin, double tMax,
    std::vector<std::shared_ptr<Object>> objects) {
  double closestT = inf;
  std::shared_ptr<Object> closestObject;

  for (std::shared_ptr<Object> object : objects) {
    auto [t1, t2] = (object->intersectRay(O, D));

    if (t1 > tMin && t1 < tMax && t1 < closestT) {
      closestT = t1;
      closestObject = object;
    }
    if (t2 > tMin && t2 < tMax && t2 < closestT) {
      closestT = t2;
      closestObject = object;
    }
  }
  return std::make_tuple(closestT, closestObject);
}

bool isLightBlocked(std::shared_ptr<Object> closestObject,
                    std::vector<std::shared_ptr<Object>> objects,
                    Eigen::Vector3d P_I,
                    std::shared_ptr<displayStructs::LightSource> lS,
                    Eigen::Vector3d l) {
  for (std::shared_ptr<Object> object : objects) {
    if (object != closestObject) {
      auto [t1, t2] = object->intersectRay(P_I, l);
      double t = -inf;
      t = std::min(t1, t2);
      if (t < 0) {
        t = (t == t2) ? t = t1 : t = t2;
      }

      Eigen::Vector3d v = lS->P_F - P_I;
      if (t >= 0 && t < v.norm()) {
        return true;
      }
    }
  }
  return false;
}

std::tuple<int, int, int> calculateLighting(
    std::vector<std::shared_ptr<displayStructs::LightSource>> lightSources,
    displayStructs::Camera camera, Eigen::Vector3d D, double t,
    std::shared_ptr<Object> closestObject,
    std::vector<std::shared_ptr<Object>> objects) {
  utilsStructs::materialK K = closestObject->getK();

  Eigen::Vector3d I_A(0, 0, 0);
  Eigen::Vector3d I_D(0, 0, 0);
  Eigen::Vector3d I_E(0, 0, 0);

  for (std::shared_ptr<displayStructs::LightSource> lS : lightSources) {
    Eigen::Vector3d I_F = lS->I_F;
    Eigen::Vector3d P_F = lS->P_F;

    Eigen::Vector3d P_I(0, 0, 0);
    Eigen::Vector3d n(0, 0, 0);
    Eigen::Vector3d l(0, 0, 0);
    Eigen::Vector3d r(0, 0, 0);
    Eigen::Vector3d v(0, 0, 0);

    P_I = camera.O + t * (D - camera.O);
    n = closestObject->getNormal(P_I);
    l = (lS->P_F - P_I) / (lS->P_F - P_I).norm();
    r = 2 * ((l.dot(n)) * n) - l;
    v = -D / D.norm();

    double F_D = std::max(n.dot(l), 0.0);
    double F_E = std::max(std::pow(r.dot(v), closestObject->getM()), 0.0);

    bool isBlocked = isLightBlocked(closestObject, objects, P_I, lS, l);
    if (isBlocked) {
      I_F(0) = 0;
      I_F(1) = 0;
      I_F(2) = 0;
    }

    I_D(0) += I_F(0) * K.Kd(0) * F_D;
    I_D(1) += I_F(1) * K.Kd(1) * F_D;
    I_D(2) += I_F(2) * K.Kd(2) * F_D;

    I_E(0) += I_F(0) * K.Ke(0) * F_E;
    I_E(1) += I_F(1) * K.Ke(1) * F_E;
    I_E(2) += I_F(2) * K.Ke(2) * F_E;
  }

  I_A(0) = camera.I_A(0) * K.Ka(0);
  I_A(1) = camera.I_A(1) * K.Ka(1);
  I_A(2) = camera.I_A(2) * K.Ka(2);

  utilsStructs::Color color = closestObject->getColor();

  int R = color.R * (I_A(0) + I_D(0) + I_E(0));
  int G = color.G * (I_A(1) + I_D(1) + I_E(1));
  int B = color.B * (I_A(2) + I_D(2) + I_E(2));

  R = std::min(R, 255);
  G = std::min(G, 255);
  B = std::min(B, 255);

  return std::make_tuple(R, G, B);
}

utilsStructs::Color traceRay(
    displayStructs::Camera camera, Eigen::Vector3d D,
    std::vector<std::shared_ptr<displayStructs::LightSource>> lightSources,
    std::vector<std::shared_ptr<Object>> objects) {
  auto [closestT, closestObject] =
      closestIntersection(camera.O, D, 0, inf, objects);

  if (closestObject == nullptr) {
    return utilsStructs::Color(BACKGROUND_COLOR);
  }
  if (closestT != inf) {
    auto [R, G, B] = calculateLighting(lightSources, camera, D, closestT,
                                       closestObject, objects);
    return utilsStructs::Color(R, G, B);
  }
  return utilsStructs::Color(BACKGROUND_COLOR);
}
}  // namespace utils
