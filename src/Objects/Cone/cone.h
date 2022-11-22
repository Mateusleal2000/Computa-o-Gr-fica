#ifndef CONE_H_
#define CONE_H_

#include <eigen3/Eigen/Dense>
#include <memory>
#include <tuple>

#include "../../Display/displayStructs.h"
#include "../../Matrix/matrix.h"
#include "../../Utils/utilsStructs.h"
#include "../Object/object.h"
#include "../Plane/plane.h"

class Cone : public Object {
    enum INTERSECTION_TYPE { BASE,
                             SURFACE };

   public:
    Cone(utilsStructs::materialK k, double shininess, double radius,
         Eigen::Vector3d center, double height, Eigen::Vector3d dCone)
        : Object(k, shininess, utilsStructs::OBJ_TYPE::CONE),
          radius(radius),
          center(center),
          height(height),
          coneDir(dCone) {
        this->vertex = center + dCone * height;
        baseLid = nullptr;
    };

    Cone(utilsStructs::materialK k, double shininess, double radius,
         Eigen::Vector3d center, Eigen::Vector3d vertex)
        : Object(k, shininess, utilsStructs::OBJ_TYPE::CONE), radius(radius), center(center), vertex(vertex) {
        baseLid = nullptr;
    };

    double getRadius();
    Eigen::Vector3d getCenter();
    Eigen::Vector3d getNormal(Eigen::Vector3d P_I);
    std::tuple<double, double> intersectRay(Eigen::Vector3d, Eigen::Vector3d);

    void scale(double x, double y, double z);
    void scale(double radiusScale, double heightScale);
    void shear(double delta, matrix::SHEAR_AXIS axis);
    void translate(double x, double y, double z, Eigen::Matrix4d wc);
    void rotate(double theta, matrix::AXIS axis);
    Cone reflection(matrix::REFLECTION_AXIS axis);
    void returnToWorld(Eigen::Matrix4d cw);
    void generateLids();

   private:
    INTERSECTION_TYPE intersectionType;
    double radius;
    double height;
    Eigen::Vector3d center;
    Eigen::Vector3d coneDir;
    Eigen::Vector3d vertex;
    std::unique_ptr<Plane> baseLid;

    double onSurface(Eigen::Vector3d, Eigen::Vector3d, double, double);
};
#endif