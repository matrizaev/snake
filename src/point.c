#include "point.h"

int dot_product(point_t a, point_t b)
{
    return a.x * b.x + a.y * b.y;
}
