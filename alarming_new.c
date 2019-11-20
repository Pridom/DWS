#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int compare(struct tm* currentTime, struct tm* alarmTime){
        return (currentTime->tm_hour == alarmTime->tm_hour) && (currentTime->tm_min == alarmTime->tm_min);
}

void displayTime(struct tm* myTime){
	char buffer[80];
	strftime(buffer, 80, "%a %Y-%m-%d \n %H:%M:%S \n", myTime);
    puts(buffer);
}

void displayAlarm(struct tm* alarm){
	char buffer[80];
	strftime(buffer, 80, "%H:%M \n", alarm);
	puts(buffer);
}


int main(){
	time_t timeinfo;
	struct tm* currentTime = malloc(sizeof(struct tm));
	struct tm* alarmTime = malloc(sizeof(struct tm));

	time(&timeinfo);
	currentTime = localtime(&timeinfo);

	currentTime->tm_year = 2019 - 1900;
	currentTime->tm_mon = 1 - 1;
	currentTime->tm_mday = 1;
	currentTime->tm_hour = 0;
	currentTime->tm_min = 0;
	currentTime->tm_sec = 0;

	mktime(currentTime);

	memset(alarmTime, 0, sizeof(struct tm));
	alarmTime->tm_min = 1;
	mktime(alarmTime);

	while(!compare(currentTime, alarmTime)){
		displayTime(currentTime);
		displayAlarm(alarmTime);
		currentTime->tm_sec++;
		mktime(currentTime);
		sleep(1);
	}

	printf("=====ALARM RINGING=====\n");
	printf("=====CURRENT TIME=====\n");
	displayTime(currentTime);
	printf("=====ALARM TIME=====\n");
	displayAlarm(alarmTime);

	return 0;
}



