#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <ncurses.h>

//saving current time info in struct tm;

struct tm* newTime; 
struct tm* myTime;
time_t rawtime, testtime;

//ctrl + c displays a new clock 
void handler(int sig) {
	char buffer[80];
	time(&testtime);
	newTime = localtime(&testtime);

	newTime->tm_year = 2019;
	newTime->tm_mon = 8;
	newTime->tm_mday = 18;
	newTime->tm_hour = 13;
	newTime->tm_min = 24;
	newTime->tm_sec = 50;

	mktime(newTime);

	while(1){
		system("clear");

		time(&testtime);
	    newTime->tm_sec++;

	    mktime(newTime);
		strftime(buffer, 80, "%a %m-%d \n %H:%M:%S \a", newTime);
		puts(buffer);
		sleep(1);
	}
}

//gets key input asynchronously;
int getAsncKeyState(){
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


int main(){
	char buffer[80];

	time(&rawtime);
	myTime = localtime(&rawtime);

	myTime->tm_year = 2019;
	myTime->tm_mon = 10;
	myTime->tm_mday = 14;
	myTime->tm_hour = 23;
	myTime->tm_min = 59;
	myTime->tm_sec = 50;
	
	mktime(myTime);

	signal(SIGINT, handler);

	while(1){
		system("clear");
		getAsncKeyState();
		time(&rawtime);
	    myTime->tm_sec++;

	    mktime(myTime);
		strftime(buffer, 80, "%a %m-%d \n %H:%M:%S \a", myTime);
		puts(buffer);
		sleep(1);
	}
	return 0;
}
