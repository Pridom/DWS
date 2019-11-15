#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>


//gets the time and saves it into the struct tm
struct tm* setTime(time_t* timeinfo, struct tm* myTime){
	time(timeinfo);
	myTime = localtime(timeinfo);

	printf("Hour - Min - Sec: ");
	scanf("%d %d %d", myTime->tm_hour, myTime->tm_min, myTime->tm_sec);
	fflush(stdin);
	printf("YYYY-MM-DD: ");
	scanf("%d %d %d", myTime->tm_year - 1900, myTime->tm_mon - 1,
	       myTime->tm_mday);
	fflush(stdin);

	mktime(myTime);

	return myTime;
}


//displays the time based on the info in struct tm
void displayTime(time_t* timeinfo, struct tm* myTime){
	//temporary storage for saving the string to display the time
	char buffer[80];

	//gets the current time (seconds)
	time(timeinfo);
	myTime = localtime(timeinfo);

	mktime(myTime);

	while(1){
		//clears the screen
		system("clear");

		time(timeinfo);

		//increases myTime by 1 sec
		myTime->tm_sec++;
		mktime(myTime);

		//displays time in the given format
		strftime(buffer, 80, "%a %y-%m-%d \n %H:%M:%S \n", myTime);
		puts(buffer);
		sleep(1);
	}
}

int main(){
	time_t timeinfo;
	struct tm* myTime = { 0, };

	time(timeinfo);
	myTime = localtime(&timeinfo);

	myTime = setTime(&timeinfo, myTime);
	displayTime(&timeinfo, myTime);

	return 0;
}





