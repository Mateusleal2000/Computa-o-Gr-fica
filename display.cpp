#include "display.h"
#include "sphere.h"

namespace display
{
    std::vector<int> scene(double viewPortWidth, double viewPortHeight, double nRow, double nCol, double dWindow, Eigen::Vector3d O, Eigen::Vector3d D, Eigen::Vector3d I_F, Eigen::Vector3d P_F, Eigen::Vector3d K, Sphere s)
    {
        double deltaX = viewPortWidth / nCol;
        double deltaY = viewPortHeight / nRow;
        double x, y;
        std::vector<int> pixelVector;

        for (int r = 0; r < nRow; r++)
        {
            y = (viewPortHeight / 2) - (deltaY / 2) - (r * deltaY);
            for (int c = 0; c < nCol; c++)
            {
                x = -(viewPortWidth / 2) + (deltaX / 2) + (c * deltaX);
                D(0) = x - O(0);
                D(1) = y - O(1);
                D(2) = -dWindow;
                std::tuple<int, int, int> color = utils::traceRay(O, D, I_F, P_F, K, s);

                pixelVector.push_back(std::get<0>(color));
                pixelVector.push_back(std::get<1>(color));
                pixelVector.push_back(std::get<2>(color));
            }
        }
        return pixelVector;
    }

    int draw(double nRow, double nCol, std::vector<int> pixelVector, std::string output)
    {
        std::ofstream fout(output);
        if (fout.fail())
        {
            return -1;
        }
        fout << "P3\n";
        fout << nCol << " " << nRow << "\n";
        fout << "255\n";

        for (auto pixel : pixelVector)
        {
            fout << pixel << " ";
        }
        return 1;
    }
}
