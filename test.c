#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

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


void getTime(struct tm* currentTime){
	while(1){

	}
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
		time(&rawtime);
	    myTime->tm_sec++;

	    mktime(myTime);
		strftime(buffer, 80, "%a %m-%d \n %H:%M:%S \a", myTime);
		puts(buffer);
		sleep(1);
	}
	return 0;
}
