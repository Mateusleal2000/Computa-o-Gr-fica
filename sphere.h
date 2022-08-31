#include <tuple>
#include <eigen3/Eigen/Dense>
class Sphere
{
public:
    Sphere(Eigen::Vector3d center, double radius, std::tuple<int, int, int> color)
    {
        this->center = center;
        this->radius = radius;
        this->color = color;
    };
    ~Sphere(){};
    double getRadius();
    Eigen::Vector3d getCenter();
    std::tuple<int, int, int> getColor();

private:
    Eigen::Vector3d center;
    double radius;
    std::tuple<int, int, int> color;
};