/*  Ted Cowan, CS3210 Lab 3 Skeleton File */

/*
 * Andrew Lane
 * CS3210
 * W01272253
 * 9-12-16
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    void *buf;
    int inputFile;
    struct stat fileStat;
    int offset, len;

    offset = atoi(argv[2]);
    len = strlen(argv[3]);

    if (argc != 4) {
        printf("Usage: zap <filename> <offset> <textstring>\n");
        return 1;
    }

    inputFile = open(argv[1], O_RDWR);
    if (inputFile < 0) {
        perror("Cannot open input file");
        return 1;
    }
    if (fstat(inputFile, &fileStat)) {
        perror("fstat() failed");
        return 1;
    }

    buf = mmap((void *)0, fileStat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, inputFile, 0);
    memcpy((void *)buf + offset, argv[3], len);
    msync(buf, fileStat.st_size, MS_ASYNC);
    munmap(buf, fileStat.st_size);

    close(inputFile);
    return 0;
}

