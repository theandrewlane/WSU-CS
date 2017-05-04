/*
	Lab #5 - Threads & Synchronization
	Name: Andrew Lane
    Class: CS3100
    3/20/16
*/

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <err.h>

WINDOW *topwin, *botwin;
//Create Threads
pthread_t winThreads[2];
//Create the mutex lock
pthread_mutex_t ncurses;

void *countUp(void *ptr) {
    int i = 0, key;

    while (1) {
        pthread_mutex_lock(&ncurses);
        wprintw(topwin, "Count up: %d\n", i++);
        wrefresh(topwin);
        pthread_mutex_unlock(&ncurses);
        key = getch();
        if (key != ERR) {
            break;
        }
    }
    return NULL;
}

void *countDown(void *ptr) {
    int i = 0, key;

    while (1) {
        pthread_mutex_lock(&ncurses);
        wprintw(botwin, "Count down: %d\n", i--);
        wrefresh(botwin);
        pthread_mutex_unlock(&ncurses);
        key = getch();
        if (key != ERR) {
            break;
        }
    }
    return NULL;
}

int main(int argc, char **argv) {
    int tlines, blines;

    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    nodelay(stdscr, TRUE);
    tlines = LINES / 2 - 1;
    blines = LINES - tlines - 1;
    topwin = newwin(tlines, COLS, 0, 0);
    scrollok(topwin, TRUE);
    botwin = newwin(blines, COLS, tlines + 1, 0);
    scrollok(botwin, TRUE);
    move(tlines, 0);
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_BLUE, COLOR_BLACK);
        wattron(topwin, COLOR_PAIR(1));
        wattron(botwin, COLOR_PAIR(2));
        wattron(stdscr, COLOR_PAIR(3));
    }
    hline('_', 200);
    refresh();

    //Thread code goes here!

    //Initialize Mutex
    if (pthread_mutex_init(&ncurses, NULL) != 0) {
        printf("\nError initializing mutex\n");
        return 1;
    }

    //Create Threads
    if (pthread_create(&(winThreads[0]), NULL, &countUp, NULL) != 0 ||
        pthread_create(&(winThreads[1]), NULL, &countDown, NULL) != 0) {
        printf("\nError creating thread");
        return 1;
    }

    //Wait for Thread termination
    pthread_join(winThreads[0], NULL);
    pthread_join(winThreads[1], NULL);

    //Destory Mutex
    pthread_mutex_destroy(&ncurses);

    usleep(3000000);
    endwin();

    return 0;
}
