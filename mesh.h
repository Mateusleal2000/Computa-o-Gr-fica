#ifndef MESH_H_
#define MESH_H_

#include <Eigen/Dense>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "matrix.h"
#include "object.h"

class Mesh : public Object {
 public:
  Mesh(utilsStructs::materialK k, double shininess, std::string path);
  Mesh(utilsStructs::materialK k, double shininess,
       std::vector<Eigen::Vector4d> vertices,
       std::vector<Eigen::Vector4d> normals, std::vector<Eigen::Vector3d> edges,
       std::vector<Eigen::Vector4d> faces);
  std::tuple<double, double> intersectRay(Eigen::Vector3d, Eigen::Vector3d);
  Eigen::Vector3d getNormal(Eigen::Vector3d P_I);
  void applyMatrixVertices(Eigen::Matrix4d);
  void applyMatrixNormals(Eigen::Matrix4d);
  void scale(double x, double y, double z);
  void shear(double delta, matrix::SHEAR_AXIS axis);
  void translate(double x, double y, double z);
  void rotate(double theta, matrix::AXIS axis);
  Mesh reflection(matrix::REFLECTION_AXIS axis);
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