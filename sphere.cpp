#include "sphere.h"

#include <Eigen/Dense>
#include <iostream>

std::tuple<double, double> Sphere::intersectRay(Eigen::Vector3d O,
                                                Eigen::Vector3d D) {
  double a, b, c;
  double delta;
  double r = this->radius;
  double inf = std::numeric_limits<double>::infinity();
  Eigen::Vector3d w = O - this->getCenter();

  a = D.dot(D);
  b = 2 * (w.dot(D));
  c = w.dot(w) - (r * r);

  delta = (b * b) - (4 * a * c);

  if (delta < 0) {
    return std::make_tuple(inf, inf);
  }

  double t1 = (-b + std::sqrt(delta)) / (2 * a);
  double t2 = (-b - std::sqrt(delta)) / (2 * a);

  return std::make_tuple(t1, t2);
}

double Sphere::getRadius() { return radius; }

Eigen::Vector3d Sphere::getCenter() { return center; }

Eigen::Vector3d Sphere::getNormal(Eigen::Vector3d P_I) {
  return ((P_I - this->center) / this->radius);
}

// void Sphere::applyMatrixVertices(Eigen::Matrix4d m) {
//   for (Eigen::Vector4d &v : vertices) {
//     v = m * v;
//   }
//   std::cout << "matriz aplicada"
//             << "\n";
//   return;
// }

// void Sphere::applyMatrixNormals(Eigen::Matrix4d m) {
//   for (Eigen::Vector4d &n : normals) {
//     n = (m * n).normalized();
//   }
//   std::cout << "matriz aplicada"
//             << "\n";
//   return;
// }

void Sphere::scale(double s) {
  // Eigen::Matrix4d m = matrix::scale(x, y, z);
  // applyMatrixVertices(m);
  this->radius = this->radius * s;
  /*if (x != y || x != z) {
    applyMatrixNormals((m.transpose()).inverse());
  }*/
  return;
}

// void Sphere::shear(double delta, matrix::SHEAR_AXIS axis) {
//   Eigen::Matrix4d m = matrix::shear(delta, axis);
//   applyMatrixVertices(m);
//   // applyMatrixNormals((m.transpose()).inverse());
//   applyMatrixNormals((m.transpose()).inverse());
//   return;
// }

void Sphere::translate(double x, double y, double z) {
  /*Eigen::Matrix4d m = matrix::translate(x, y, z);
  applyMatrixVertices(m);*/
  this->center(0) = x;
  this->center(1) = y;
  this->center(2) = z;
  return;
}
// void Sphere::rotate(double theta, matrix::AXIS axis) {
//   Eigen::Matrix4d m = matrix::rotate(theta, axis);
//   applyMatrixVertices(m);
//   applyMatrixNormals(m);
//   return;
// }

Sphere Sphere::reflection(matrix::REFLECTION_AXIS axis) {
  Eigen::Matrix4d m = matrix::reflection(axis);
  Eigen::Vector4d aux(this->center(0), this->center(1), this->center(2), 1);
  Eigen::Vector4d aux2 = m * aux;
  Sphere reflectedSphere(this->getK(), this->getM(), this->radius,
                         Eigen::Vector3d(0, 50, -120));

  return reflectedSphere;
}