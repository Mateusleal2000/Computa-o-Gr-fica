#ifndef MESH_H_
#define MESH_H_

#include <Eigen/Dense>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "object.h"

class Mesh : public Object {
 public:
  Mesh(utilsStructs::materialK k, double shininess, std::string path);
  std::tuple<double, double> intersectRay(Eigen::Vector3d, Eigen::Vector3d);
  Eigen::Vector3d getNormal(Eigen::Vector3d P_I);

 private:
  // Lista de vertices
  // Lista de arestas
  // Lista de faces
  std::vector<Eigen::Vector4d> vertices;
  std::vector<Eigen::Vector4d> normals;
  std::vector<Eigen::Vector3d> edges;
  std::vector<Eigen::Vector4d> faces;
  Eigen::Vector3d normal;
  std::string objName;
};

#endif