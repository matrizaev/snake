#ifndef POINT_H
#define POINT_H

typedef struct
{
    int x, y;
} point_t;

int dot_product(const point_t a, const point_t b);

#endif
