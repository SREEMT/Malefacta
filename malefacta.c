#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

//creating the struct needed for the terminal interface
struct termios orig_termios;

//Error handling function
void die(const char *s){
	perror(s);
	exit(1);
}

//function to disable Raw Mode;
void disableRawMode(){
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
		die("tcsetattr");
}

//function to eneable raw mode in the editor (uses termios)
void enableRawMode(){
	if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
		die("tcgetattr");
	atexit(disableRawMode);

	struct termios raw = orig_termios;
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP |IXON);
	raw.c_iflag &= ~(ICRNL | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_flag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;

	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
		die("tcsetattr");
}

//main that makes the whole program work
int main(){
	//calls the function to eneable raw mode
	enableRawMode();

	//sets up the raw input for the user in the terminal
	//User can type 'q' to quit
	while (1){
		char c = '\0';
		if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN)
			die("read");
		
		if (iscntrl(c)){
			printf("%d\n", c);
		}else{
			printf("%d ('%c')\n", c, c);
		}
		if (c == 'q') break;
	}
	return 0;
}
