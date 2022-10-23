#ifndef MATRIX_H_
#define MATRIX_H_

#include <Eigen/Dense>
#include <iostream>
#include <memory>
#include <tuple>

namespace matrix {
enum AXIS { X, Y, Z };
enum class SHEAR_AXIS { XY, XZ, YX, YZ, ZX, ZY };
enum class REFLECTION_AXIS { XY, XZ, YZ };

Eigen::Matrix4d scale(double x, double y, double z);

Eigen::Matrix4d shear(double delta, SHEAR_AXIS axis);

Eigen::Matrix4d translate(double x, double y, double z);

Eigen::Matrix4d rotate(double theta, AXIS axis);

Eigen::Matrix4d reflection(REFLECTION_AXIS axis);
}  // namespace matrix

#endif
