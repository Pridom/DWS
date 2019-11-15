#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int getch(void)
{
  int ch;
  struct termios buf;
  struct termios save;

   tcgetattr(0, &save);
   buf = save;
   buf.c_lflag &= ~(ICANON|ECHO);
   buf.c_cc[VMIN] = 1;
   buf.c_cc[VTIME] = 0;
   tcsetattr(0, TCSAFLUSH, &buf);
   ch = getchar();
   tcsetattr(0, TCSAFLUSH, &save);
   return ch;
}

int kbhit(void){
	struct termios oldt, newt;
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if(ch != EOF){
		ungetc(ch, stdin);
		return 1;
	}

	return 0;
}

int getAsnc(){
	int key = 0;
	
	if(kbhit()){
		key = getch();
		if(key == 65 || key == 66 || key == 67 || key == 68 ||
		   key == 97 || key == 98 || key == 99 || key == 100) {
			switch(key) {
				case 65:
					printf("A");
					break;
				case 66:
					printf("B");
					break;
				case 67:
					printf("C");
					break;
				case 68:
					printf("D");
					break;
				case 97:
					printf("a");
					break;
				case 98:
					printf("b");
					break;
				case 99:
					printf("c");
					break;
				case 100:
					printf("d");
					break;
				default:
					printf("You pressed somethin' else \n");
					break;
			}
		}
	}

	return 0;
} 



