#ifndef SPHERE_H_
#define SPHERE_H_

#include <eigen3/Eigen/Dense>
#include <memory>
#include <tuple>

#include "displayStructs.h"
#include "matrix.h"
#include "object.h"
#include "utilsStructs.h"

class Sphere : public Object {
   public:
    Sphere(utilsStructs::materialK k, double shininess, double radius,
           Eigen::Vector3d center)
        : Object(k, shininess), radius(radius), center(center){};
    double getRadius();
    Eigen::Vector3d getCenter();
    Eigen::Vector3d getNormal(Eigen::Vector3d P_I);
    std::tuple<double, double> intersectRay(Eigen::Vector3d, Eigen::Vector3d);

    /*void applyMatrixVertices(Eigen::Matrix4d);
    void applyMatrixNormals(Eigen::Matrix4d);*/
    void scale(double s);
    // void shear(double delta, matrix::SHEAR_AXIS axis);
    void translate(double x, double y, double z, Eigen::Matrix4d wc);
    // void rotate(double theta, matrix::AXIS axis);
    Sphere reflection(matrix::REFLECTION_AXIS axis);

   private:
    Eigen::Vector3d center;
    double radius;
    Eigen::Matrix4d wc;
};
#endif