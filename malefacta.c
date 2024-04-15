#include <stdio.h>
#include <termios.h>
#include <unistd.h>

//function to eneable raw mode in the editor
void enableRawMode(){
        struct termios raw;

        tcgetattr(STDIN_FILENO, &raw);

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