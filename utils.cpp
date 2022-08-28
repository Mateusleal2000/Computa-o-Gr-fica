#include "utils.h"
#include "sphere.h"

namespace utils
{
    std::tuple<float, float> intersectRaySphere(Eigen::Vector3d O, Eigen::Vector3d D, Sphere s)
    {
        float a, b, c;
        float delta;
        float r = s.getRadius();
        Eigen::Vector3d CO = O - s.getCenter();

        a = D.dot(D);
        b = 2 * (CO.dot(D));
        c = CO.dot(CO) - (r * r);

        delta = (b * b) - (4 * a * c);

        if (delta < 0)
        {
            float inf = std::numeric_limits<float>::infinity();
            return std::make_tuple(inf, inf);
        }

        float t1 = (-b + std::sqrt(delta)) / (2 * a);
        float t2 = (-b - std::sqrt(delta)) / (2 * a);

        return std::make_tuple(t1, t2);
    }

    std::tuple<int, int, int> traceRay(Eigen::Vector3d O, Eigen::Vector3d D, float tMin, float tMax, Sphere &s)
    {
        auto [t1, t2] = utils::intersectRaySphere(O, D, s);
        if (t1 >= tMin && t1 < tMax)
        {
            return s.getColor();
        }
        return std::make_tuple(255, 255, 255);
    }
}
