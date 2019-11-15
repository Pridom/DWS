#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#include "myio.h"

struct tm* setTime(time_t* timeinfo, struct tm* setTime){
	time(*timeinfo);
	setTime = localtime(*timeinfo);

	printf("Hour - Min - Sec: ");
	scanf("%d %d %d", setTime->tm_hour, setTime->tm_min, setTime->tm_sec);
	fflush(stdin);
	printf("YYYY-MM-DD: ");
	scanf("%d %d %d", setTime->tm_year - 1900, setTime->tm_mon - 1,
	       setTime->tm_mday);
	fflush(stdin);

	mktime(setTime);

	return setTime;
}

void displayTime(time_t* timeinfo, struct tm* setTime){
	while(1){




