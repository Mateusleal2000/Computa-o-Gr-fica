#include "cylinder.h"

#include <Eigen/Dense>
#include <iostream>

std::tuple<double, double> Cylinder::intersectRay(Eigen::Vector3d O,
                                                  Eigen::Vector3d D) {
  double a, b, c;
  double delta;
  double r = this->radius;
  double inf = std::numeric_limits<double>::infinity();
  double validPoint = inf;

  Eigen::Vector3d w = O - this->getCenter();

  a = D.transpose() * M * D;
  b = 2 * w.transpose() * M * D;
  c = (w.transpose() * M * w) - std::pow(radius, 2);

  delta = (b * b) - (4 * a * c);

  if (delta < 0) {
    return std::make_tuple(validPoint, validPoint);
  }

  double t1 = (-b + std::sqrt(delta)) / (2 * a);
  double t2 = (-b - std::sqrt(delta)) / (2 * a);

  Eigen::Vector3d P_I;

  std::tuple<double, double> tBottom = baseLid->intersectRay(O, D);
  std::tuple<double, double> tUpper = topLid->intersectRay(O, D);

  // Segunda verificação - Raio/Plano da base

  // double tBase = (O - center).dot(-cylinderDir) / (D.dot(-cylinderDir));
  // double tBase = -(O - center).dot(dCil) / (D.dot(dCil));

  // P_I = O + tBase * D;
  P_I = O + std::get<0>(tBottom) * D;
  double test1 = (P_I - center).norm();
  if (test1 > 0 && test1 <= radius) {
    intersectionType = BASE;
    validPoint = std::get<0>(tBottom);
  }

  // Terceira verificação - Raio/Plano do topo
  // Eigen::Vector3d Ct = center + height * dCil;

  // double tTop = -(O-topCenter).dot(cylinderDir) / (D.dot(cylinderDir));
  // P_I = O + tTop * D;
  P_I = O + std::get<0>(tUpper) * D;
  double test2 = (P_I - topCenter).norm();
  if (test2 > 0 && test2 <= radius) {
    if (validPoint > std::get<0>(tUpper)) {
      intersectionType = TOP;
      validPoint = std::get<0>(tUpper);
    }
  }

  // Primeira verificação - Raio/Superfície
  double t = onSurface(O, D, t1, t2);

  if (validPoint > t) {
    intersectionType = SURFACE;
    validPoint = t;
  }

  return std::make_tuple(validPoint, validPoint);
}

double Cylinder::getRadius() { return radius; }

Eigen::Vector3d Cylinder::getCenter() { return center; }

Eigen::Vector3d Cylinder::getNormal(Eigen::Vector3d P_I) {
  if (intersectionType == TOP) {
    return cylinderDir;
  }

  if (intersectionType == BASE) {
    return -cylinderDir;
  }

  Eigen::Vector3d n = M * (P_I - center);
  return n / n.norm();
}

double Cylinder::onSurface(Eigen::Vector3d O, Eigen::Vector3d D, double t1,
                           double t2) {
  Eigen::Vector3d P_I_1;
  Eigen::Vector3d P_I_2;
  double validPoint = std::numeric_limits<double>::infinity();
  P_I_1 = O + t1 * D;
  P_I_2 = O + t2 * D;

  double test1 = (P_I_1 - center).dot(cylinderDir);
  double test2 = (P_I_2 - center).dot(cylinderDir);

  if (test1 > 0 && test1 <= height) {
    if (t1 > 0) {
      validPoint = t1;
    }
  }
  if (test2 > 0 && test2 <= height) {
    if (t2 > 0 && validPoint > t2) {
      validPoint = t2;
    }
  }
  return validPoint;
}