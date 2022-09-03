#include "object.h"

double Object::getDWindow()
{
    return dWindow;
}
utilsStructs::Color Object::getColor()
{
    return color;
}
Eigen::Vector3d Object::getCenter()
{
    return center;
}
Eigen::Vector3d Object::getK()
{
    return K;
}