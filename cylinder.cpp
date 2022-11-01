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

  P_I = O + std::get<0>(tBottom) * D;
  double test1 = (P_I - center).norm();
  if (test1 > 0 && test1 <= radius) {
    intersectionType = BASE;
    validPoint = std::get<0>(tBottom);
  }

  // Terceira verificação - Raio/Plano do topo

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

void Cylinder::scale(double radiusScale, double heightScale) {
  this->height *= heightScale;
  this->radius *= radiusScale;
  return;
}
void Cylinder::shear(double delta, matrix::SHEAR_AXIS axis) {
  Eigen::Matrix4d m = matrix::shear(delta, axis);
  return;
}
void Cylinder::translate(double x, double y, double z, Eigen::Matrix4d wc) {
  Eigen::Vector4d auxCenter(x, y, z, 1);
  Eigen::Vector4d newCenter = wc * auxCenter;
  this->center = newCenter.head<3>();

  Eigen::Vector4d auxDir(cylinderDir(0), cylinderDir(1), cylinderDir(2), 0);
  Eigen::Vector4d newDir = wc * auxDir;
  this->cylinderDir = newDir.head<3>();
  generateLids();
  return;
}
void Cylinder::rotate(double theta, matrix::AXIS axis) {
  Eigen::Matrix4d m = matrix::rotate(theta, axis);
  return;
}
Cylinder Cylinder::reflection(matrix::REFLECTION_AXIS axis) {
  Eigen::Matrix4d m = matrix::reflection(axis);
  Cylinder reflectedCylinder(this->getK(), this->getM(), this->radius,
                             this->center, this->height, this->cylinderDir);

  return reflectedCylinder;
}

void Cylinder::generateLids() {
  this->M = Eigen::Matrix<double, 3, 3>::Identity() -
            this->cylinderDir * this->cylinderDir.transpose();

  this->topCenter = this->center + this->height * this->cylinderDir;

  this->baseLid =
      std::make_unique<Plane>(this->K, this->m, center, -cylinderDir);

  this->topLid =
      std::make_unique<Plane>(this->K, this->m, topCenter, cylinderDir);
  return;
}