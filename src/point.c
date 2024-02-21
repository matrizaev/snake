#include "point.h"

inline int dot_product(const point_t a, const point_t b)
{
    return a.x * b.x + a.y * b.y;
}
