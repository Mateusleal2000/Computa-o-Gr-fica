#ifndef MESH_H_
#define MESH_H_

#include<vector>

class Mesh {
 public:
  std::vector<double> getVertexList();
  std::vector<double> getFacesList();
  std::vector<double> getEdgesList();
 private:
  // Lista de vertices
  // Lista de arestas
  // Lista de faces
};



#endif