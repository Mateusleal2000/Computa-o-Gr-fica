#include "mesh.h"

#include <regex>

std::vector<std::string> split(std::string s, std::string del = " ") {
  std::vector<std::string> values;
  int start, end = -1 * del.size();
  do {
    start = end + del.size();
    end = s.find(del, start);
    values.push_back(s.substr(start, end - start));
  } while (end != -1);
  return values;
}

Mesh::Mesh(utilsStructs::materialK k, double shininess, std::string path)
    : Object(k, shininess) {
  // std::cout << "Comecou o construtor" << "\n";
  std::ifstream objFile;
  objFile.open(path);
  std::string line;
  double id = 0;
  while (getline(objFile, line)) {
    if (line[0] == 'o') {
      std::vector<std::string> object_info = split(line);
      this->objName = object_info[1];
    }

    if (line[0] == 'v') {
      std::vector<std::string> vertices_values = split(line);

      Eigen::Vector4d v(0.0, 0.0, 0.0, 1.0);
      v(0) = std::stod(vertices_values[1]);
      v(1) = std::stod(vertices_values[3]);
      v(2) = std::stod(vertices_values[2]);
      this->vertices.push_back(v);
    }
    if (line[0] == 'v' && line[1] == 'n') {
      std::vector<std::string> normal_values = split(line);
      Eigen::Vector4d vn(0.0, 0.0, 0.0, 1.0);
      vn(0) = std::stod(normal_values[1]);
      vn(1) = std::stod(normal_values[3]);
      vn(2) = std::stod(normal_values[2]);

      this->normals.push_back(vn);
    }
    if (line[0] == 'f') {
      std::vector<std::string> face_values = split(line);
      Eigen::Vector4d f(0.0, 0.0, 0.0, 0.0);
      double v1 = std::stod(split(face_values[1], "//")[0]);
      double v2 = std::stod(split(face_values[2], "//")[0]);
      double v3 = std::stod(split(face_values[3], "//")[0]);
      double n = std::stod(split(face_values[3], "//")[1]);

      Eigen::Vector3d e1(id++, v1, v2);
      Eigen::Vector3d e2(id++, v2, v3);
      Eigen::Vector3d e3(id++, v3, v1);

      this->edges.push_back(e1);
      this->edges.push_back(e2);
      this->edges.push_back(e3);

      f(0) = e1[0];
      f(1) = e2[0];
      f(2) = e3[0];
      f(3) = n;
      this->faces.push_back(f);
    }
  }
  objFile.close();
  // std::cout << "terminou o construtor" << "\n";
}

std::tuple<double, double> Mesh::intersectRay(Eigen::Vector3d O,
                                              Eigen::Vector3d D) {
  double inf = std::numeric_limits<double>::infinity();
  // Eigen::Vector4d O_4d(O[0], O[1], O[2], 1);
  // Eigen::Vector4d D_4d(D[0], D[1], D[2], 1);
  Eigen::Vector3d P_I(0, 0, 0);
  double t = inf;
  // double validPoint = inf;
  for (auto &face : this->faces) {
    double vertex_id = (this->edges[int(face[0])])[1];
    Eigen::Vector3d n =
        (this->normals[int((this->vertices[int(vertex_id)])[3])]).head<3>();
    double t_aux =
        -(O - this->vertices[int(vertex_id)].head<3>()).dot(n) / D.dot(n);
    if (t_aux > 0 && t_aux < t) {
      P_I = O + t_aux * D;
      // P1
      Eigen::Vector3d P1 = this->vertices[int(vertex_id)].head<3>();
      //// P2
      Eigen::Vector3d P2 = this->vertices[int(vertex_id) + 1].head<3>();
      //// P3
      Eigen::Vector3d P3 = this->vertices[int(vertex_id) + 2].head<3>();

      Eigen::Vector3d r1 = P2 - P1;
      Eigen::Vector3d r2 = P3 - P1;
      double c1 = ((P3 - P_I).cross(P1 - P_I)).dot(n) / (r1.cross(r2)).dot(n);
      double c2 = ((P1 - P_I).cross(P2 - P_I)).dot(n) / (r1.cross(r2)).dot(n);
      double c3 = 1 - c1 - c2;
      if (c1 >= 0 && c2 >= 0 && c3 >= 0) {
        std::cout << c1 + c2 + c3 << "\n";
        t = t_aux;
        this->normal = n;
      }
    }
  }
  return std::make_tuple(t, t);
}

Eigen::Vector3d Mesh::getNormal(Eigen::Vector3d P_I) {
  // std::cout << this->normal[0] << " " << this->normal[1] << " " <<
  // this->normal[2] << "\n";
  return this->normal;
}