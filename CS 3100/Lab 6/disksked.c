/*
Name: Andrew Lane
Lab: #6
Class: CS3100
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int MAXSIZE = 8;

int fcfs(int tracks[]) {
    int i = 0;
    int sum = 0;
    int diff = 0;

    printf("FCFS: Start:%d", tracks[0]);

    for (i = 1; i <= MAXSIZE; i++) {
        diff = abs(tracks[i - 1] - tracks[i]);
        printf(" %d:%d", tracks[i], diff);
        sum = sum + diff;
    }

    printf(" Total:%d\n", sum);
    return 0;
}

int *ascArraySort(int *a, int SIZE) {
    int i, pass, hold;
    for (pass = 1; pass <= (SIZE - 1); pass++)
        for (i = 0; i <= (SIZE - 2); i++)
            if (a[i] > a[i + 1]) {
                hold = a[i];
                a[i] = a[i + 1];
                a[i + 1] = hold;
            }
    // printf("\n\nData items in ascending order\n\n");
    //  for (i=0; i <= (SIZE-1); i++)
    //  printf("%4d", a[i]);
    //printf("\n\n");
    return a;
}

int *dscArraySort(int *a, int SIZE) {
    int i, pass, hold;
    for (pass = 1; pass <= (SIZE - 1); pass++)
        for (i = 0; i <= (SIZE - 2); i++)
            if (a[i] < a[i + 1]) {
                hold = a[i];
                a[i] = a[i + 1];
                a[i + 1] = hold;
            }
    /* printf("\n\nData items in descending order\n\n");
      for (i=0; i <= (SIZE-1); i++)
      printf("%4d", a[i]);
    printf("\n\n");*/
    return a;
}

int scan(int tracks[]) {
    int i;
    int g_then[MAXSIZE];
    int l_then[MAXSIZE];
    int *l_sorted, *g_sorted;
    int g_size = 0;
    int l_size = 0;
    int sum = 0;
    int diff = 0;

    printf("SCAN: Start:%d", tracks[0]);

    for (i = 1; i <= MAXSIZE; i++) {
        if (tracks[i] >= tracks[0]) {
            g_then[g_size] = tracks[i];
            g_size++;
            //printf("\n%d < %d\n", tracks[i - 1], tracks[i]);
        }
        else {

            l_then[l_size] = tracks[i];
            l_size++;
            // printf("\n%d > %d\n", tracks[i - 1], tracks[i]);
        }
    }

    l_sorted = ascArraySort(l_then, l_size);
    g_sorted = ascArraySort(g_then, g_size);

    for (i = 0; i < g_size; i++) {
        if (i == 0) {
            diff = abs(tracks[0] - g_sorted[i]);
        }
        if (i > 0) {
            diff = abs(g_sorted[i - 1] - g_sorted[i]);
        }
        printf(" %d:%d", g_sorted[i], diff);
        sum += diff;
    }

    for (i = 0; i < l_size; i++) {
        if (i == 0 && g_size > 0) {
            diff = abs(l_sorted[i] - g_sorted[g_size - 1]);
        }
        if (i == 0 && g_size < 1) {
            diff = abs(l_sorted[i] - tracks[0]);

        }
        if (i > 0) {
            diff = abs(l_sorted[i] - l_sorted[i - 1]);
        }

        printf(" %d:%d", l_sorted[i], diff);
        sum += diff;
    }
    printf(" Total:%d\n", sum);
    return 0;
}

int sstf(int tracks[]) {
    int sorted[MAXSIZE], diffArray[MAXSIZE], diff, i, j, temp, s = 0, k = 0, x = 0, sum = 0;

    sorted[0] = tracks[0];
    for (i = 0; i < MAXSIZE; i++) {
        s = INT_MAX;
        for (j = i + 1; j < MAXSIZE + 1; j++) {
            diff = abs(tracks[i] - tracks[j]);
            if (diff <= s) {
                if (diff != s) {

                    s = diff;
                    x = j;
                }
            }

        }
        sum += s;
        diffArray[i] = s;
        temp = tracks[i + 1];
        tracks[i + 1] = tracks[x];
        tracks[x] = temp;
        sorted[k++] = tracks[i + 1];
        //printf("SORTED %d\n", sorted[i]);

    }
    printf("SSTF: Start:%d", tracks[0]);
    for (i = 0; i < MAXSIZE; i++)
        printf(" %d:%d", sorted[i], diffArray[i]);
    printf(" Total:%d\n", sum);
    return 0;
}

int c_scan(int tracks[]) {
    int i;
    int g_than[MAXSIZE];
    int l_than[MAXSIZE];
    int *l_sorted, *g_sorted;
    int g_size = 0;
    int l_size = 0;
    int sum = 0;
    int diff = 0;

    printf("C_SCAN: Start:%d", tracks[0]);

    for (i = 1; i <= MAXSIZE; i++) {
        if (tracks[i] >= tracks[0]) {
            g_than[g_size] = tracks[i];
            g_size++;
            //printf("\n%d < %d\n", tracks[i - 1], tracks[i]);
        }
        else {
            l_than[l_size] = tracks[i];
            l_size++;
            // printf("\n%d > %d\n", tracks[i - 1], tracks[i]);
        }
    }

    l_sorted = dscArraySort(l_than, l_size);
    g_sorted = ascArraySort(g_than, g_size);

    for (i = 0; i < g_size; i++) {
        if (i == 0) {
            diff = abs(tracks[0] - g_sorted[i]);
        }
        if (i > 0) {
            diff = abs(g_sorted[i - 1] - g_sorted[i]);
        }
        sum += diff;
        printf(" %d:%d", g_sorted[i], diff);
    }

    for (i = 0; i < l_size; i++) {
        if (i == 0 && g_size > 0) {
            diff = abs(l_sorted[i] - g_sorted[g_size - 1]);
        }

        if (i == 0 && g_size < 1) {
            diff = abs(l_sorted[i] - tracks[0]);
        }
        if (i > 0) {
            diff = abs(l_sorted[i] - l_sorted[i - 1]);
        }

        printf(" %d:%d", l_sorted[i], diff);
        sum += diff;
    }
    printf(" Total:%d\n", sum);
    return 0;

}

int main(int argc, char *argv[]) {
    int tracks[9] = {atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]),
                     atoi(argv[7]), atoi(argv[8]), atoi(argv[9])};
    fcfs(tracks);
    sstf(tracks);
    scan(tracks);
    c_scan(tracks);
    return 0;
}


