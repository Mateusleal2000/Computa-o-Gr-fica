#include "utils.h"
#include "sphere.h"
#include <iostream>

namespace utils
{
    double inf = std::numeric_limits<double>::infinity();

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
            return std::make_tuple(inf, inf);
        }

        double t1 = (-b + std::sqrt(delta)) / (2 * a);
        double t2 = (-b - std::sqrt(delta)) / (2 * a);

        return std::make_tuple(t1, t2);
    }

    std::tuple<double, double, double> traceRay(Eigen::Vector3d O, Eigen::Vector3d D, displayStructs::LightSource lS, Eigen::Vector3d K, Sphere &s)
    {
        auto [t1, t2] = utils::intersectRaySphere(O, D, s);
        if (t1 != inf)
        {
            auto I_F = lS.I_F;
            auto P_F = lS.P_F;
            Eigen::Vector3d P_I(0, 0, 0);
            Eigen::Vector3d I_D(0, 0, 0);
            Eigen::Vector3d I_E(0, 0, 0);
            Eigen::Vector3d n(0, 0, 0);
            Eigen::Vector3d l(0, 0, 0);
            Eigen::Vector3d r(0, 0, 0);
            Eigen::Vector3d v(0, 0, 0);
            Eigen::Vector3d center = s.getCenter();

            auto t = std::max(t1, t2);
            P_I = O + (-t) * (D - O);
            n = (P_I - center) / s.getRadius();
            l = (P_F - P_I) / (P_F - P_I).norm();
            r = 2 * ((l.dot(n)) * n) - l;
            v = -D / D.norm();

            double F_D = std::max(n.dot(l), 0.0);
            double F_E = std::max(r.dot(v), 0.0);

            I_D(0) = I_F(0) * K(0) * F_D;
            I_D(1) = I_F(1) * K(1) * F_D;
            I_D(2) = I_F(2) * K(2) * F_D;

            I_E(0) = I_F(0) * K(0) * F_E;
            I_E(1) = I_F(1) * K(1) * F_E;
            I_E(2) = I_F(2) * K(2) * F_E;

            utilsStructs::Color color = s.getColor();

            double R = color.R * (std::min((I_D(0) + I_E(0)), 1.0));
            double G = color.G * (std::min((I_D(1) + I_E(1)), 1.0));
            double B = color.B * (std::min((I_D(2) + I_E(2)), 1.0));

            return std::make_tuple(R, G, B);
        }
        return std::make_tuple(100, 100, 100);
    }
}
