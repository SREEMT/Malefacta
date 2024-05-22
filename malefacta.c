#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

//creating the struct needed for the terminal interface
struct termios orig_termios;

//function to disable Raw Mode;
void disableRawMode(){
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

//function to eneable raw mode in the editor (uses termios)
void enableRawMode(){
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);

    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


int main(){

    //calls the function to eneable raw mode
    enableRawMode();

    //sets up the raw input for the user in the terminal
    //User can type 'q' to quit
    char c;
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q');
    return 0;
}
