#ifndef CILINDER_H_
#define CILINDER_H_

#include <Eigen/Dense>
#include <memory>
#include <tuple>

#include "displayStructs.h"
#include "object.h"
#include "utilsStructs.h"
#include "plane.h"

class Cylinder : public Object {
public:
    Cylinder(utilsStructs::Color color, utilsStructs::materialK k, double shininess,
        double radius, Eigen::Vector3d center, double height, Eigen::Vector3d dCil)
		: Object(color, k, shininess), radius(radius), center(center), height(height), cylinderDir(dCil) {
            M = Eigen::Matrix<double, 3, 3>::Identity() - dCil * dCil.transpose();
			topCenter = center + height * dCil;
            baseLid = std::make_unique<Plane>(color, k, shininess,center, -cylinderDir);
            topLid = std::make_unique<Plane>(color, k, shininess, topCenter, cylinderDir);
        };
    double getRadius();
    Eigen::Vector3d getCenter();
    Eigen::Vector3d getNormal(Eigen::Vector3d P_I);
    std::tuple<double, double> intersectRay(Eigen::Vector3d, Eigen::Vector3d);

private:
	double radius;
	double height;
    Eigen::Vector3d center;
	Eigen::Vector3d cylinderDir;
    Eigen::Vector3d topCenter;
    Eigen::Matrix<double, 3, 3> M;
    std::unique_ptr<Plane> topLid;
    std::unique_ptr<Plane> baseLid;
	
    double onSurface(Eigen::Vector3d, Eigen::Vector3d, double, double);

};
#endif