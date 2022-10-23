#include "matrix.h"
#define M_PI 3.14159265358979323846

namespace matrix {
Eigen::Matrix4d scale(double x, double y, double z) {
  Eigen::Matrix4d m;
  m << x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1;
  return m;
}

Eigen::Matrix4d shear(double delta, SHEAR_AXIS axis) {
  Eigen::Matrix4d m;
  delta = delta * M_PI / 180.0;
  switch (axis) {
    case matrix::SHEAR_AXIS::XY:
      m << 1, 0, 0, 0, std::tan(delta), 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1;
      break;
    case matrix::SHEAR_AXIS::XZ:
      m << 1, 0, 0, 0, 0, 1, 0, 0, std::tan(delta), 0, 1, 0, 0, 0, 0, 1;
      break;
    case matrix::SHEAR_AXIS::YX:
      m << 1, std::tan(delta), 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1;
      break;
    case matrix::SHEAR_AXIS::YZ:
      m << 1, 0, 0, 0, 0, 1, 0, 0, 0, std::tan(delta), 1, 0, 0, 0, 0, 1;
      break;
    case matrix::SHEAR_AXIS::ZX:
      m << 1, 0, std::tan(delta), 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1;
      break;
    case matrix::SHEAR_AXIS::ZY:
      m << 1, 0, 0, 0, 0, 1, std::tan(delta), 0, 0, 0, 1, 0, 0, 0, 0, 1;
      break;
    default:
      break;
  }
  return m;
}

Eigen::Matrix4d translate(double x, double y, double z) {
  Eigen::Matrix4d m;
  m << 1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1;
  return m;
}

Eigen::Matrix4d rotate(double theta, AXIS axis) {
  Eigen::Matrix4d m;
  theta = theta * M_PI / 180.0;
  if (axis == AXIS::X) {
    m << 1, 0, 0, 0, 0, std::cos(theta), -std::sin(theta), 0, 0,
        std::sin(theta), std::cos(theta), 0, 0, 0, 0, 1;

    std::cout << "Rotate X axis"
              << "\n";
  } else if (axis == AXIS::Y) {
    m << std::cos(theta), 0, std::sin(theta), 0, 0, 1, 0, 0, -std::sin(theta),
        0, std::cos(theta), 0, 0, 0, 0, 1;
    std::cout << "Rotate Y axis"
              << "\n";
  } else if (axis == AXIS::Z) {
    m << std::cos(theta), -std::sin(theta), 0, 0, std::sin(theta),
        std::cos(theta), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1;
    std::cout << "Rotate Z axis"
              << "\n";
  }
  return m;
}

Eigen::Matrix4d reflection(REFLECTION_AXIS axis) {
  Eigen::Matrix4d m;
  switch (axis) {
    case matrix::REFLECTION_AXIS::XY:
      m << 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1;
      break;
    case matrix::REFLECTION_AXIS::XZ:
      m << 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1;
      break;
    case matrix::REFLECTION_AXIS::YZ:
      m << -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1;
      break;
    default:
      break;
  }
  return m;
}
}  // namespace matrix