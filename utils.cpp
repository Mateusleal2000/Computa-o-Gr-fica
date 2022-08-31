#include "utils.h"
#include "sphere.h"
#include <fstream>

namespace utils
{
    std::tuple<double, double> intersectRaySphere(Eigen::Vector3d O, Eigen::Vector3d D, Sphere s)
    {
        double a, b, c;
        double delta;
        double r = s.getRadius();

        a = D.dot(D);
        b = 2 * (s.getCenter().dot(D));
        c = s.getCenter().dot(s.getCenter()) - (r * r);

        delta = (b * b) - (4 * a * c);

        if (delta < 0)
        {
            double inf = std::numeric_limits<double>::infinity();
            return std::make_tuple(inf, inf);
        }

        double t1 = (-b + std::sqrt(delta)) / (2 * a);
        double t2 = (-b - std::sqrt(delta)) / (2 * a);

        return std::make_tuple(t1, t2);
    }

    std::tuple<int, int, int> traceRay(Eigen::Vector3d O, Eigen::Vector3d D, double tMin, double tMax, Sphere &s)
    {
        auto [t1, t2] = utils::intersectRaySphere(O, D, s);
        double inf = std::numeric_limits<double>::infinity();
        if (t1 != inf)
        {
            return s.getColor();
        }
        return std::make_tuple(100, 100, 100);
    }
}
