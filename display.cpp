#include "display.h"

namespace display
{
    std::vector<int> scene(displayStructs::Viewport viewport, Eigen::Vector3d O, std::vector<std::shared_ptr<displayStructs::LightSource>> lightSources, std::vector<std::shared_ptr<Sphere>> spheres)
    {
        double deltaX = viewport.width / viewport.nColumns;
        double deltaY = viewport.height / viewport.nRows;
        double x, y;
        std::vector<int> pixelVector;
        Eigen::Vector3d D(0, 0, 0);

        for (int r = 0; r < viewport.nRows; r++)
        {
            y = (viewport.height / 2) - (deltaY / 2) - (r * deltaY);
            for (int c = 0; c < viewport.nColumns; c++)
            {
                x = -(viewport.width / 2) + (deltaX / 2) + (c * deltaX);
                D(0) = x - O(0);
                D(1) = y - O(1);
                D(2) = -viewport.dWindow;
                std::tuple<int, int, int> color = utils::traceRay(O, D, lightSources, spheres[0]);

                pixelVector.push_back(std::get<0>(color));
                pixelVector.push_back(std::get<1>(color));
                pixelVector.push_back(std::get<2>(color));
            }
        }
        return pixelVector;
    }

    int draw(double width, double height, std::vector<int> pixelVector, std::string output)
    {
        std::ofstream fout(output);
        if (fout.fail())
        {
            return -1;
        }
        fout << "P3\n";
        fout << height << " " << width << "\n";
        fout << "255\n";

        for (auto pixel : pixelVector)
        {
            fout << pixel << " ";
        }
        return 1;
    }
}
