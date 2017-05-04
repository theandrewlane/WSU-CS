//
// Created by Andrew Lane on 9/22/16.
//

#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <time.h>
#include <stdlib.h>

/*
 * Usage: userinfo -? -h -t -u username
-h show hostname
-t show time and date
-u show username, uid, gid, home dir, shell and GECOS
-? show usage
 */

//-h show hostname
void printHostName() {
    char hname[256];
    gethostname(hname, 255);
    printf("hostname: %s", hname);
}

//-u show username, uid, gid, home dir, shell and GECOS
void printUserInfo() {
    struct passwd *pwd;
    pwd = getpwnam(optarg);
    printf("username: %s\nuser ID: %u\ngroup ID: %u\nhome directory: %s\nshell: %s\ngecos information: %s",
           pwd->pw_name, pwd->pw_uid, pwd->pw_gid, pwd->pw_dir, pwd->pw_shell, pwd->pw_gecos);
}

//-t show time and date
void printDateTime() {
    time_t t;
    time(&t);
    printf("Time: %s", ctime(&t));
}

int getUserInput(int argc, char *argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "htu:?")) != -1) {
        switch (opt) {
            case 'h':
                printHostName();
                break;
            case 't':
                printDateTime();
                break;
            case 'u':
                printUserInfo();
                break;
            default :
                printf("\nUsage: userinfo -? -h -t -u username");
                printf("\n-h show hostname\n-t show time and date\n-u show username, uid, gid, home dir, shell and GECOS\n-? show usage\n");
                return 1;
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    return getUserInput(argc, argv);
}

