#include "object.h"

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