#include "minunit.h"
#include "snake_obj.h"

char *test_snake_obj()
{
    snake_t snake = {0};
    snake_init(&snake);
    mu_assert(snake.length == 1, "Snake length is not 1");
    mu_assert(snake.speed == 1.0, "Snake speed is not 1");
    mu_assert(snake.body[0].x == 1 && snake.body[0].y == 1, "Snake position is not 1, 1");
    mu_assert(snake.direction.x == 0 && snake.direction.y == 0, "Snake direction is not 0, 0");

    snake_set_direction(&snake, (point_t){1, 0});
    snake_move(&snake);

    mu_assert(snake.body[0].x == 3 && snake.body[0].y == 1, "Snake position is not 3, 1");
    mu_assert(snake.direction.x == 1 && snake.direction.y == 0, "Snake direction is not 0, 1");

    mu_assert(snake_try_eat_food(&snake, (point_t){2, 1}), "Snake did not eat");
    mu_assert(snake.length == 2, "Snake length is not 2");
    mu_assert(snake.body[1].x == snake.body[0].x && snake.body[1].y == snake.body[0].y, "Snake's tail position is not the same as the head position");

    snake_set_direction(&snake, (point_t){-1, 0});
    mu_assert(snake.direction.x == 1 && snake.direction.y == 0, "Snake direction is -1, 0");

    snake_set_direction(&snake, (point_t){0, 0});
    mu_assert(snake.direction.x == 1 && snake.direction.y == 0, "Snake direction is 0, 0");

    snake_speedup(&snake);
    mu_assert(abs(snake.speed - 1.1) < 0.01, "Snake speed is not 1.1");

    mu_assert(snake_try_hit_walls(&snake, 0, 0), "Snake did not hit walls");

    return NULL;
}

char *all_tests()
{

    mu_suite_start();

    mu_run_test(test_snake_obj);

    return NULL;
}

RUN_TESTS(all_tests);