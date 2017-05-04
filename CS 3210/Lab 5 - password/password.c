//
// Created by Andrew Lane - W01272253
// 9/29/16
// CS3210 - Lab5 password
//


#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <term.h>

//Doesn't have to be global, but okay
char userInput[128];
//Get input from the user, providing the prompt
char *promptGetInput(char *prompt) {
    printf("%s: ", prompt);
    fflush(stdout); //Flush dat
    //Get Input, trim, and store globally
    strtok(fgets(userInput, 10, stdin), "\n");
    return userInput;
}

//Move the cursor somewhere
void moveCursor(char *cursor, int x, int y) {
    char *esc_sequence;
    esc_sequence = tparm(cursor, y, x);
    putp(esc_sequence);
}

int main(int argc, char **argv) {
    int nrows, ncolumns;
    //Create backup of terminal settings
    struct termios attribs, attribs_backup;
    tcgetattr(0, &attribs);
    attribs_backup = attribs;

    setupterm(NULL, fileno(stdout), (int *) 0);
    tigetnum("xen1");
    putp(tigetstr("clear"));

    // Get screen dimensions
    nrows = tigetnum("lines");
    ncolumns = tigetnum("cols");

    // Get cursor - ref pg. 202
    char *cursor;
    cursor = tigetstr("cup");

    //Create coordinates
    int x = ncolumns / 2 - 10;
    int y = nrows / 2;

    //Moves the cursor to the middle line of the screen and the middle column - 10
    moveCursor(cursor, x, y);

    //Prompts for a user name with the prompt "username: "
    promptGetInput("Username");

    //Moves the cursor down one line and the middle column - 10
    moveCursor(cursor, x, y + 1);

    //Turn off terminal echo
    attribs.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &attribs);

    //Prompts for a password with the prompt "password: "
    char *password = promptGetInput("Password");

      //Make sure the user enters a password. If not, prompt them again, and again...
//    while (strlen(password) <= 1 && strcmp(password, "(null)")) {
//        // Moves the cursor to the last line - 1, column 0
//        moveCursor(cursor, 0, nrows - 1);
//        printf("No password entered, please try again");
//        moveCursor(cursor, x, y + 1);
//        password = promptGetInput("Password");
//    }

    moveCursor(cursor, 0, nrows - 2);

    //Logic to handle empty user input
    if (strlen(password) <= 1 && strcmp(password, "(null)")) printf("Password is <>");
    else printf("Password is <%s>", password);

    // Restore terminal settings + move cursor before exiting
    moveCursor(cursor, 0, nrows - 1);
    tcsetattr(0, TCSANOW, &attribs_backup);
    return 0;
}