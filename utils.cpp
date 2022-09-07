#include "utils.h"

namespace utils
{
    double inf = std::numeric_limits<double>::infinity();

    // std::tuple<double, double> intersectRaySphere(Eigen::Vector3d O, Eigen::Vector3d D, std::shared_ptr<Sphere> s)
    // {
    //     double a, b, c;
    //     double delta;
    //     double r = s.get()->getRadius();

    //     a = D.dot(D);
    //     b = 2 * (s.get()->getCenter().dot(D));
    //     c = s.get()->getCenter().dot(s.get()->getCenter()) - (r * r);

    //     delta = (b * b) - (4 * a * c);

    //     if (delta < 0)
    //     {
    //         return std::make_tuple(inf, inf);
    //     }

    //     double t1 = (-b + std::sqrt(delta)) / (2 * a);
    //     double t2 = (-b - std::sqrt(delta)) / (2 * a);

    //     return std::make_tuple(t1, t2);
    // }

    std::tuple<double, double, double> traceRay(Eigen::Vector3d O, Eigen::Vector3d D, std::vector<std::shared_ptr<displayStructs::LightSource>> lightSources, std::vector<std::shared_ptr<Object>> objects)
    {
        auto lS = lightSources[0];
        Object *obj = objects[0].get();

        auto [t1, t2] = obj->intersectRay(O, D);
        if (t1 != inf)
        {
            auto I_F = lS.get()->I_F;
            auto P_F = lS.get()->P_F;
            auto K = obj->getK();
            auto t = std::max(t1, t2);

            Eigen::Vector3d I_D(0, 0, 0);
            Eigen::Vector3d I_E(0, 0, 0);

            auto [F_D, F_E] = obj->calculateLighting(lS, O, D, t);

            I_D(0) = I_F(0) * K(0) * F_D;
            I_D(1) = I_F(1) * K(1) * F_D;
            I_D(2) = I_F(2) * K(2) * F_D;

            I_E(0) = I_F(0) * K(0) * F_E;
            I_E(1) = I_F(1) * K(1) * F_E;
            I_E(2) = I_F(2) * K(2) * F_E;

            utilsStructs::Color color = obj->getColor();

            double R = color.R * (std::min((I_D(0) + I_E(0)), 1.0));
            double G = color.G * (std::min((I_D(1) + I_E(1)), 1.0));
            double B = color.B * (std::min((I_D(2) + I_E(2)), 1.0));

            return std::make_tuple(R, G, B);
        }
        return std::make_tuple(100, 100, 100);
    }
}
