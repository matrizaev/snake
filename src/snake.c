#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>

#include "point.h"
#include "snake_obj.h"

#define SNAKE_COLOR_PAIR 1
#define BERRY_COLOR_PAIR 2

point_t new_berry()
{
    return (point_t){rand() % (COLS - 1) + 1, rand() % (LINES - 1) + 1};
}

void draw_snake(snake_t *snake)
{
    attron(COLOR_PAIR(SNAKE_COLOR_PAIR));
    mvaddch(snake->body[0].y, snake->body[0].x, 'O');
    for (size_t i = 1; i < snake->length; i++)
    {
        mvaddch(snake->body[i].y, snake->body[i].x, 'o');
    }
    attroff(COLOR_PAIR(SNAKE_COLOR_PAIR));
}

void draw_berry(point_t berry)
{
    attron(COLOR_PAIR(BERRY_COLOR_PAIR));
    mvaddch(berry.y, berry.x, '@');
    attroff(COLOR_PAIR(BERRY_COLOR_PAIR));
}

void draw_stats(WINDOW *win, snake_t *snake)
{
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    mvprintw(0, 2, "Score: %d", snake->length - 1);
}

WINDOW *init_ncurses()
{
    WINDOW *win = initscr();
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    keypad(win, true);
    nodelay(win, true);
    curs_set(0);
    start_color();
    init_pair(SNAKE_COLOR_PAIR, COLOR_GREEN, COLOR_BLACK);
    init_pair(BERRY_COLOR_PAIR, COLOR_RED, COLOR_BLACK);
    wrefresh(win);
    return win;
}

int main()
{

    WINDOW *win = init_ncurses();

    snake_t snake = {0};

    snake_init(&snake);
    point_t berry = new_berry();
    bool running = true;
    while (running)
    {
        int pressed = wgetch(win);
        point_t direction = snake.direction;
        switch (pressed)
        {
        case KEY_UP:
            direction = (point_t){0, -1};
            break;
        case KEY_DOWN:
            direction = (point_t){0, 1};
            break;
        case KEY_LEFT:
            direction = (point_t){-1, 0};
            break;
        case KEY_RIGHT:
            direction = (point_t){1, 0};
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
        draw_stats(win, &snake);
        draw_snake(&snake);
        draw_berry(berry);
        usleep(125000 / snake.speed);
    }
    wgetch(win);
    endwin();
    return 0;
}