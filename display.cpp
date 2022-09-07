#include "display.h"

namespace display
{
    std::vector<int> scene(displayStructs::Viewport viewport, displayStructs::Camera camera, std::vector<std::shared_ptr<displayStructs::LightSource>> lightSources, std::vector<std::shared_ptr<Object>> objects)
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
                // D(0) = x - x;
                // D(1) = y - y;
                D(0) = x - camera.O(0);
                D(1) = y - camera.O(1);
                D(2) = -viewport.dWindow;

                // displayStructs::Camera cameraTest(Eigen::Vector3d(x, y, 0), camera.I_A);
                utilsStructs::Color color = utils::traceRay(camera, D, lightSources, objects);

                pixelVector.push_back(color.R);
                pixelVector.push_back(color.G);
                pixelVector.push_back(color.B);
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
