#ifndef SNAKE_OBH_H
#define SNAKE_OBH_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "point.h"

#define MAX_SNAKE_LENGTH 100
#define MAX_SNAKE_SPEED 10

typedef struct
{
    size_t length;
    point_t body[MAX_SNAKE_LENGTH];
    point_t direction;
    float speed;
} snake_t;

snake_t snake_create();
void snake_move(snake_t *snake);
void snake_grow(snake_t *snake);
void snake_set_direction(snake_t *snake, const point_t direction);
void snake_speedup(snake_t *snake);
bool snake_try_eat_food(snake_t *snake, const point_t food);
bool snake_try_eat_self(const snake_t *const snake);
bool snake_try_hit_walls(const snake_t *const snake, int field_width, int field_height);

#endif
