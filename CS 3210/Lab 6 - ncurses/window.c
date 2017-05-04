//Lab6 - Ncurses App
//CS3210 - 10/7/16
//I used my CS3100 submission for most of this - Why reinvent the wheel Ted! :)

/*
	//Lab #5 - Threads & Synchronization
	// Name: Andrew Lane
    //Class: CS3100
    //3/20/16
*/

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include <err.h>

WINDOW *topwin, *botwin;

void *count() {
    int t = 0, b = 0, key;
    while (1) {
        wprintw(topwin, "Count up: %d\n", t++);
        wrefresh(topwin);
        wprintw(botwin, "Count down: %d\n", b--);
        wrefresh(botwin);
        key = getch();
        usleep(250000);
        if (key != ERR) {
            delwin(botwin);
            delwin(topwin);
            break;
        }
    }
    return NULL;
}

int main(int argc, char **argv) {
    int topLines, bottomLines;
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    nodelay(stdscr, TRUE);
    topLines = LINES / 2 - 1;
    bottomLines = LINES - topLines - 1;
    topwin = newwin(topLines, COLS, 0, 0);
    scrollok(topwin, TRUE);
    botwin = newwin(bottomLines, COLS, topLines + 1, 0);
    scrollok(botwin, TRUE);
    move(topLines, 0);
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_BLUE, COLOR_BLACK);
        wattron(botwin, COLOR_PAIR(1));
        wattron(topwin, COLOR_PAIR(2));
        wattron(stdscr, COLOR_PAIR(3));
    }
    hline('_', 100);
    refresh();
    count();
    usleep(3000000);
    endwin();
    return 0;
}
