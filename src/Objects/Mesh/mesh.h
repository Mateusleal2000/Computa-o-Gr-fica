#ifndef MESH_H_
#define MESH_H_

#include <eigen3/Eigen/Dense>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "../Object/object.h"

class Mesh : public Object {
   public:
    Mesh(utilsStructs::materialK k, double shininess, std::string path);
    Mesh(utilsStructs::materialK k, double shininess,
         std::vector<Eigen::Vector4d> vertices,
         std::vector<Eigen::Vector4d> normals, std::vector<Eigen::Vector3d> edges,
         std::vector<Eigen::Vector4d> faces);
    std::tuple<double, double> intersectRay(Eigen::Vector3d, Eigen::Vector3d);
    Eigen::Vector3d getNormal(Eigen::Vector3d P_I);
    void returnToWorld(Eigen::Matrix4d cw);
    void applyMatrixVertices(Eigen::Matrix4d);
    void applyMatrixNormals(Eigen::Matrix4d);
    void scale(double x, double y, double z);
    void shear(double delta, matrix::SHEAR_AXIS axis);
    void translate(double x, double y, double z, Eigen::Matrix4d wc);
    void rotate(double theta, matrix::AXIS axis);
    void reflection(matrix::REFLECTION_AXIS axis, std::vector<std::shared_ptr<Object>> &objects);
    /*std::vector<Eigen::Vector4d> getNormals();
    std::vector<Eigen::Vector4d> getVertices();*/

   private:
    std::vector<Eigen::Vector4d> vertices;
    std::vector<Eigen::Vector4d> normals;
    std::vector<Eigen::Vector3d> edges;
    std::vector<Eigen::Vector4d> faces;
    Eigen::Vector3d normal;
    std::string objName;
};

#endif