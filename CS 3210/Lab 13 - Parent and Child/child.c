//
// Created by Andrew Lane on 11/19/16.
//

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE PIPE_BUF

int main(int argc, char** argv) {
    char buffer[BUFFER_SIZE];
    char *fifo_name = "/tmp/fifo1";
    int fd = open(fifo_name, O_RDONLY);

    int res;

    do {
        memset(buffer, '\0', sizeof(buffer));
        res = read(fd, buffer, BUFFER_SIZE);
        printf("%s", buffer);
    } while (res > 0);

    close(fd);
    unlink(fifo_name);

    return 0;
}
