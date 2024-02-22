#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>

#include "point.h"
#include "snake_obj.h"
#include "dbg.h"

#define SNAKE_COLOR_PAIR 1
#define BERRY_COLOR_PAIR 2

static point_t new_berry()
{
    return (point_t){.x = rand() % (COLS - 1) + 1, .y = rand() % (LINES - 1) + 1};
}

static void draw_snake(const snake_t *const snake)
{
    attron(COLOR_PAIR(SNAKE_COLOR_PAIR));
    mvaddch(snake->body[0].y, snake->body[0].x, 'O');
    for (size_t i = 1; i < snake->length; i++)
    {
        mvaddch(snake->body[i].y, snake->body[i].x, 'o');
    }
    attroff(COLOR_PAIR(SNAKE_COLOR_PAIR));
}

static void draw_berry(point_t berry)
{
    attron(COLOR_PAIR(BERRY_COLOR_PAIR));
    mvaddch(berry.y, berry.x, '@');
    attroff(COLOR_PAIR(BERRY_COLOR_PAIR));
}

static void draw_stats(WINDOW *win, size_t score)
{
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    mvprintw(0, 2, "Score: %zu", score);
}

WINDOW *init_ncurses()
{
    WINDOW *win = initscr();
    check(win != NULL, "initscr failed");
    check(wborder(win, '|', '|', '-', '-', '+', '+', '+', '+') == OK, "wborder failed");
    check(keypad(win, true) == OK, "keypad failed");
    check(nodelay(win, true) == OK, "nodelay failed");
    check(curs_set(0) != ERR, "curs_set failed");
    check(start_color() == OK, "start_solor failed");
    check(init_pair(SNAKE_COLOR_PAIR, COLOR_GREEN, COLOR_BLACK) == OK, "init_pair failed");
    check(init_pair(BERRY_COLOR_PAIR, COLOR_RED, COLOR_BLACK) == OK, "init_pair failed");
    check(wrefresh(win) == OK, "wrefresh failed");
    return win;
error:
    return NULL;
}

int main()
{

    int result = -1;

    WINDOW *win = init_ncurses();
    check(win != NULL, "failed to initialize ncurses");

    snake_t snake = snake_create();
    point_t berry = new_berry();
    bool running = true;
    while (running)
    {
        int pressed = wgetch(win);
        point_t direction = snake.direction;
        switch (pressed)
        {
        case KEY_UP:
            direction = (point_t){.x = 0, .y = -1};
            break;
        case KEY_DOWN:
            direction = (point_t){.x = 0, .y = 1};
            break;
        case KEY_LEFT:
            direction = (point_t){.x = -1, .y = 0};
            break;
        case KEY_RIGHT:
            direction = (point_t){.x = 1, .y = 0};
            break;
        case '\e':
            running = false;
            break;
        default:
            break;
        }

        if (snake_try_hit_walls(&snake, COLS, LINES) || snake_try_eat_self(&snake))
        {
            running = false;
        }

        if (snake_try_eat_food(&snake, berry))
        {
            berry = new_berry();
        }

        erase();
        snake_set_direction(&snake, direction);
        snake_move(&snake);
        draw_stats(win, snake.length);
        draw_snake(&snake);
        draw_berry(berry);
        usleep(125000 / snake.speed);
    }
    wgetch(win);
    result = 0;
error:
    endwin();
    return result;
}
