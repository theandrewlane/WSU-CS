/*
 CS 3100 Lab 2 - by Andrew Bryan Lane
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

void cmdExit(int argc, char **argv) {
    if(argc > 1){
        errno = EINVAL;
        perror("exit command failed");
    }
    if(argc <= 1){
        exit(0);
    }
}

int getParameters(char *cmd, char **argv) {
    char *token;
    int argc = 0;
    token = strtok(cmd, " \t\n");
    while(token != NULL){
        argv[argc] = token;
        argc++;
        token = strtok(NULL, " \t\n");
    }
    argv[argc] = NULL;
    return argc;
}

void execute(char** argv)
{
    pid_t pid;
    int childStatus;


    if ((pid = fork()) < 0) {
        perror("forking error");
        exit(1);
    }

    else if (pid == 0) {
        if (execvp(*argv, argv) < 0) {
            errno = ENOENT;
            perror("execvp() failed");
            exit(1);
        }
    }
    else {
        while(wait(&childStatus) !=pid);
    }
}



int main(int argc, char **argv) {

    char cmd[1024];
    char *rc;
    int myArgc = 0;
    char *myArgv[1000];
    while (1) {

        printf("nanosh: ");
        fflush(stdout);
        rc = fgets(cmd, sizeof(cmd), stdin);
        if (rc == NULL) {
            exit(0);
        }
        myArgc = getParameters(cmd, myArgv);
        // if no words typed: restart loop
        if (myArgc == 0) {
            continue;
        }

        // if the first word is "exit", terminate the program
        if (strcmp(myArgv[0], "exit") == 0) {
            cmdExit(myArgc, myArgv);
            continue;
        }


        if (strcmp(myArgv[0], "cd") == 0) {
            if (myArgc == 1) {
                myArgv[0] = (char *) "chdir(getenv(\"HOME\")";
                execute(myArgv);
                continue;
            }
            if (myArgc > 3) {
                errno = EINVAL;
                perror("Invalid number of parameters to cd");
                continue;
            }
            else {
                execute(myArgv);
                continue;
            }
        }

        if (strcmp(myArgv[0], "pwd") == 0) {
            if (myArgc > 2) {
                errno = EINVAL;
                perror("Invalid number of parameters to pwd");
                continue;
            }
            else {
                execute(myArgv);
                continue;
            }
        }

        if (myArgv[0]){
            execute(myArgv);
            continue;
        }

    }
}