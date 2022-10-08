#ifndef MESH_H_
#define MESH_H_

#include<vector>
#include <string>
#include <Eigen/Dense>
#include <iostream>
#include <fstream>

class Mesh {
 public:
  Mesh(std::string path);
  std::vector<double> getVertexList();
  std::vector<double> getFacesList();
  std::vector<double> getEdgesList();
 private:
  // Lista de vertices
  // Lista de arestas
  // Lista de faces
  std::vector<Eigen::Vector4d> vertices;
  std::vector<Eigen::Vector3d> normal;
};



#endif