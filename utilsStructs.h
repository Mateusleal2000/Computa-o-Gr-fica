#ifndef UTILSSTRUCTS_H_
#define UTILSSTRUCTS_H_

namespace utilsStructs
{
    struct Color
    {
        Color(int bg) : R(bg), G(bg), B(bg){

                                      };
        Color(int red, int green, int blue) : R(red), G(green), B(blue)
        {
        }
        int R;
        int G;
        int B;
    };

}

#endif