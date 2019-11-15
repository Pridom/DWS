#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "myio.h"
//saving current time info in struct tm;

struct tm* newTime; 
struct tm* myTime;
time_t rawtime, testtime;

//gets key input asynchronously;

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

	while(1){
		system("clear");
		
		//gets input
		getAsnc();

		time(&rawtime);
		myTime->tm_sec++;
		mktime(myTime);
		strftime(buffer, 80, "%a %m-%d \n %H:%M:%S \a", myTime);
		puts(buffer);
		sleep(1);
	}
	return 0;
}
