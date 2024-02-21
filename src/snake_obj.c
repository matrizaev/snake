
#include "snake_obj.h"
#include "dbg.h"

void snake_init(snake_t *snake)
{
    check(snake, "snake is null");
    *snake = (snake_t){
        .length = 1,
        .direction = (point_t){0, 0},
        .body = {(point_t){1, 1}},
        .speed = 1.0};
error:
    return;
}

void snake_move(snake_t *snake)
{
    check(snake, "snake is null");
    for (size_t i = snake->length - 1; i > 0; i--)
    {
        snake->body[i] = snake->body[i - 1];
    }
    snake->body[0].x += snake->direction.x * 2;
    snake->body[0].y += snake->direction.y;
error:
    return;
}

void snake_grow(snake_t *snake)
{
    check(snake, "snake is null");
    if (snake->length < MAX_SNAKE_LENGTH)
    {
        snake->length++;
        snake->body[snake->length - 1] = snake->body[snake->length - 2];
    }
error:
    return;
}

void snake_set_direction(snake_t *snake, const point_t direction)
{
    check(snake, "snake is null");
    int dir_len = dot_product(direction, direction);
    int dp = dot_product(snake->direction, direction);
    if (dir_len != 0 && dp == 0)
    {
        snake->direction.x = direction.x / dir_len;
        snake->direction.y = direction.y / dir_len;
    }
error:
    return;
}

void snake_speedup(snake_t *snake)
{
    check(snake, "snake is null");
    if (snake->speed < MAX_SNAKE_SPEED)
    {
        snake->speed += 0.1;
    }
error:
    return;
}

bool is_collision(const point_t a, const point_t b, const point_t direction)
{
    return (a.x == b.x && a.y == b.y) || ((a.x - direction.x) == b.x && a.y == b.y);
}

bool snake_test_collision(const snake_t *snake, const point_t point)
{
    check(snake, "snake is null");
    for (size_t i = 0; i < snake->length; i++)
    {
        if (is_collision(snake->body[i], point, snake->direction))
        {
            return true;
        }
    }
error:
    return false;
}

bool snake_try_eat_food(snake_t *snake, const point_t food)
{
    check(snake, "snake is null");
    if (snake_test_collision(snake, food))
    {
        snake_grow(snake);
        snake_speedup(snake);
        return true;
    }
error:
    return false;
}

bool snake_try_eat_self(const snake_t *snake)
{
    check(snake, "snake is null");
    if (snake->length > 4)
        for (size_t i = 1; i < snake->length; i++)
        {
            if (is_collision(snake->body[0], snake->body[i], snake->direction))
            {
                return true;
            }
        }
error:
    return false;
}

bool snake_try_hit_walls(const snake_t *snake, const int field_width, const int field_height)
{
    check(snake, "snake is null");
    if (snake->body[0].x < 1 || snake->body[0].x >= field_width - 1 || snake->body[0].y < 1 || snake->body[0].y >= field_height - 1)
        return true;
error:
    return false;
}
