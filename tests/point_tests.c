#include "minunit.h"
#include "point.h"

char *test_dot_product()
{
    point_t a = {0, 1};
    point_t b = {0, -1};
    point_t c = {1, 0};
    point_t d = {-1, 0};

    mu_assert(dot_product(a, a) == 1, "Dot product same direction is not 1");
    mu_assert(dot_product(a, b) == -1, "Dot product oppsite direction is not -1");
    mu_assert(dot_product(a, c) == 0, "Dot product perpendicular direction is not 0");
    mu_assert(dot_product(a, d) == 0, "Dot product perpendicular direction is not 0");
}

char *all_tests()
{

    mu_suite_start();

    mu_run_test(test_dot_product);

    return NULL;
}

RUN_TESTS(all_tests);
