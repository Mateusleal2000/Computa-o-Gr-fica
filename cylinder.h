#ifndef CILINDER_H_
#define CILINDER_H_

#include <Eigen/Dense>
#include <memory>
#include <tuple>

#include "displayStructs.h"
#include "object.h"
#include "utilsStructs.h"

class Cylinder : public Object {
public:
    Cylinder(utilsStructs::Color color, utilsStructs::materialK k, double shininess,
        double radius, Eigen::Vector3d center, double height, Eigen::Vector3d dCil)
		: Object(color, k, shininess), radius(radius), center(center), height(height), dCil(dCil) {
            M = Eigen::Matrix<double, 3, 3>::Identity() - dCil * dCil.transpose();
        };
    double getRadius();
    Eigen::Vector3d getCenter();
    Eigen::Vector3d getNormal(Eigen::Vector3d P_I);
    std::tuple<double, double> intersectRay(Eigen::Vector3d, Eigen::Vector3d);

private:
	double radius;
	double height;
    Eigen::Vector3d center;
	Eigen::Vector3d dCil;
    Eigen::Matrix<double, 3, 3> M;
};
#endif