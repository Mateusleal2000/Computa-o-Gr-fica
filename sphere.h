#include <tuple>
#include <eigen3/Eigen/Dense>
class Sphere
{
public:
    Sphere(Eigen::Vector3d center, float radius, std::tuple<int, int, int> color)
    {
        this->center = center;
        this->radius = radius;
        this->color = color;
    };
    ~Sphere(){};
    float getRadius();
    Eigen::Vector3d getCenter();
    std::tuple<int, int, int> getColor();

private:
    Eigen::Vector3d center;
    float radius;
    std::tuple<int, int, int> color;
};