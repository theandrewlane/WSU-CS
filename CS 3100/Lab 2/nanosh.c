/*
 CS 3100 Lab 2 - by Andrew Bryan Lane
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>


//This is pretty much worthless
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

int execute(char **args) {
    pid_t pid;
    pid = fork();

    switch (pid) {
        case -1:
            perror("forking error");
            break;

        case 0:
            execvp(*args, args);
            errno = ENOENT;
            perror("execvp() failed");
            exit(1);

        default:
            waitpid(pid, NULL, 0);
    }
    return 0;
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

        if (myArgc == 0) {
            continue;
        }

        // if the first word is "exit", terminate the program
        if (strcmp(myArgv[0], "exit") == 0) {
            cmdExit(myArgc, myArgv);
            continue;
        }

        if (strcmp(myArgv[0], "cd") == 0) {
            char target[1000];
            char *home = getenv("HOME");
            if (myArgc == 1) {
                snprintf( target, sizeof( target ), "%s%s%s", "chdir(", home, ")" );
                //execute((char **) target);
                chdir(home);
                continue;
            }
            if (myArgc > 2) {
                errno = EINVAL;
                perror("Invalid number of parameters to cd");
                continue;
            }
            else {
                char *input = myArgv[1];
                snprintf( target, sizeof( target ), "%s%s%s", "chdir(", input, ")" );
                //execute((char **) target);
                if(chdir(input)!= 0){
                    perror("Error running cd command");
                }
                continue;
            }
        }

        if (strcmp(myArgv[0], "pwd") == 0) {
            if (myArgc > 2) {
                errno = EINVAL;
                perror("Invalid number of parameters to pwd");
                continue;
            }
                if(myArgc > 1 && strcmp(myArgv[1],"-L") != 0 && strcmp(myArgv[1],"-P") != 0 && strcmp(myArgv[1],"-version") != 0 && strcmp(myArgv[1],"-help") != 0 && strcmp(myArgv[1],"-physical") != 0 && strcmp(myArgv[1],"-logical") != 0 ){
                    errno = EINVAL;
                    perror("Invalid parameter on pwd");
                    continue;
                }
            else {
                execute(myArgv);
                continue;
            }
        }

        //Execute the command if it's not caught in the above checks
        if (myArgv[0]){
            execute(myArgv);
            continue;
        }
        return 0;
    }
}
