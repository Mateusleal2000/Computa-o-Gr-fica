#ifndef UTILSSTRUCTS_H_
#define UTILSSTRUCTS_H_

namespace utilsStructs
{
    struct Color
    {
        Color(){};
        Color(double red, double green, double blue) : R(red), G(green), B(blue)
        {
        }
        double R;
        double G;
        double B;
    };

}

#endif