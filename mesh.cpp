#include "mesh.h"

#include <regex>

std::vector<std::string> split(std::string s, std::string del = " ") {
  std::vector<std::string> values;
  int start, end = -1 * del.size();
  do {
    start = end + del.size();
    end = s.find(del, start);
    values.push_back(s.substr(start, end - start));
    // std::cout << s.substr(start, end - start) << std::endl;
  } while (end != -1);
  return values;
}

Mesh::Mesh(std::string path) {
  std::regex vertex_regex("v\\s([-]?[0-9]+[\\.][0-9]+[\\s]?){3}");
  std::regex normals_regex("vn\\s([-]?[0-9]+[\\.][0-9]+[\\s]?){3}");

  std::ifstream objFile;
  objFile.open(path);
  std::string line;
  while (getline(objFile, line)) {
    if (line[0] == 'v') {
      std::vector<std::string> vertices_values = split(line);

      Eigen::Vector4d v(0.0, 0.0, 0.0, 1.0);
      v(0) = std::stod(vertices_values[1]);
      v(1) = std::stod(vertices_values[2]);
      v(2) = std::stod(vertices_values[3]);
      this->vertices.push_back(v);
    }
    if (line[0] == 'v' && line[1] == 'n') {
      std::vector<std::string> normal_values = split(line);
      Eigen::Vector3d vn(0.0, 0.0, 0.0);
      vn(0) = std::stod(normal_values[1]);
      vn(1) = std::stod(normal_values[2]);
      vn(2) = std::stod(normal_values[3]);

      this->normal.push_back(vn);
    }
  }
  objFile.close();

  for (auto &vertex : this->vertices) {
    std::cout << vertex << "\n";
  }
}