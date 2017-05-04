//
// Created by Andrew Lane - W01272253
// 11/4/16
// CS3210 - Lab 11: Processes and Signals
//

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int term = 0;
int counter = 0;

void sig_action_handler(int);

int main(int argc, char **argv) {

    pid_t pid = fork();
    struct sigaction act;
    switch (pid) {

        case -1:
            printf("Fork Error!\n");

        case 0:
            act.sa_handler = sig_action_handler;
            sigemptyset(&act.sa_mask);
            act.sa_flags = 0;
            sigaction(SIGHUP, &act, NULL);
            sigaction(SIGTERM, &act, NULL);
            while ("true") {
                printf("Counter = %d\n", ++counter);
                sleep(1);
                if (term != 0) {
                    return 0;
                }
            }

        default:
            printf("Child pid is %d\n", pid);
            waitpid(pid, 0, 0); //We will wait here until the child has been killed
            printf("Child has terminated and parent will now terminate.");
            return 0;
    }
}

void sig_action_handler(int sig) {
    if (sig == SIGHUP) {
        printf("HUP received by Child\n");
        counter = 0;
    }
    if (sig == SIGTERM) {
        printf("TERM received by Child\n");
        term = 1;
    }
}



