//
// Created by Andrew Lane on 11/19/16.
//

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>

#define BUFFER_SIZE PIPE_BUF

int main(int argc, char **argv) {

    char buffer[BUFFER_SIZE];
    int res, fd;
    int open_mode = O_WRONLY;
//    char *fifo_name = argv[1];
    char *fifo_name = "/tmp/fifo1";
    remove(fifo_name);


    res = mkfifo(fifo_name, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
    if (res != 0) exit(EXIT_FAILURE);


    fd = open(fifo_name, open_mode);

    if (fd == -1) {
        perror("Error opening file");
    }

    do {
        memset(buffer, '\0', sizeof(buffer));
        fgets(buffer, BUFFER_SIZE, stdin);
        res = write(fd, buffer, BUFFER_SIZE);
    } while (strncmp(buffer, "quit", BUFFER_SIZE) == -1);
    close(fd);

    return 0;
}