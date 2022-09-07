#include "utils.h"

namespace utils
{
    double inf = std::numeric_limits<double>::infinity();
    int BACKGROUND_COLOR = 100;

    utilsStructs::Color traceRay(displayStructs::Camera camera, Eigen::Vector3d D, std::vector<std::shared_ptr<displayStructs::LightSource>> lightSources, std::vector<std::shared_ptr<Object>> objects)
    {
        auto lS = lightSources[0];

        double closest_t = inf;
        std::shared_ptr<Object> closest_object;

        for (std::shared_ptr<Object> object : objects)
        {
            auto [t1, t2] = (object->intersectRay(camera.O, D));
            t1 = std::abs(t1);
            t2 = std::abs(t2);

            if (t1 != inf && t1 < closest_t)
            {
                closest_t = t1;
                closest_object = object;
            }
            if (t2 != inf && t2 < closest_t)
            {
                closest_t = t2;
                closest_object = object;
            }
        }
        if (closest_object == nullptr)
        {
            return utilsStructs::Color(BACKGROUND_COLOR);
        }
        if (closest_t != inf)
        {
            auto I_F = lS.get()->I_F;
            auto P_F = lS.get()->P_F;
            auto K = closest_object.get()->getK();
            // auto t = std::max(t1, t2);

            Eigen::Vector3d I_D(0, 0, 0);
            Eigen::Vector3d I_E(0, 0, 0);

            auto [F_D, F_E] = closest_object.get()->calculateLighting(lS, camera, D, closest_t);

            I_D(0) = I_F(0) * K(0) * F_D;
            I_D(1) = I_F(1) * K(1) * F_D;
            I_D(2) = I_F(2) * K(2) * F_D;

            I_E(0) = I_F(0) * K(0) * F_E;
            I_E(1) = I_F(1) * K(1) * F_E;
            I_E(2) = I_F(2) * K(2) * F_E;

            utilsStructs::Color color = closest_object.get()->getColor();

            int R = color.R * (camera.I_A(0) + I_D(0) + I_E(0));
            int G = color.G * (camera.I_A(1) + I_D(1) + I_E(1));
            int B = color.B * (camera.I_A(2) + I_D(2) + I_E(2));

            return utilsStructs::Color(R, G, B);
        }
        return utilsStructs::Color(BACKGROUND_COLOR);
    }
}
