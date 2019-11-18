#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char getch(){
	char ch;
	ch = getchar();
	printf("%c \n", ch);
	return ch;
}


void displayTime(struct tm* myTime){
	char buffer[80];
	strftime(buffer, 80, "%a %Y-%m-%d \n %H:%M:%S \n", myTime);
	puts(buffer);
}


void CurrentTimeShift(int* select, char* input[6]){
	*select = (*select + 1) % 6;
	printf("%s \n", input[*select]);

}

void IncreaseCurrentTime(int select, struct tm* myTime){
	switch(select){
		case 0:
			myTime->tm_sec++;
			break;
		case 1:
			myTime->tm_min++;
			break;
		case 2:
			myTime->tm_hour++;
			break;
		case 3:
			myTime->tm_year++;
			break;
		case 4:
			myTime->tm_mon++;
			break;
		case 5:
			myTime->tm_mday++;
			break;
		default:
			printf("input error \n");
	}

	mktime(myTime);
	displayTime(myTime);
}

void TimeSetting(struct tm* myTime){
	int select = 0;
	char* inputDesc[6] = {"second", "minute", "hour", "year",
		                  "mon", "day"};
	char ch;

	while(1){
		ch = getch();
		
		if(ch == 'a'){
			break;
		} else if(ch == 'b') {
			IncreaseCurrentTime(select, myTime);
		} else if(ch == 'c') {
			CurrentTimeShift(&select, inputDesc);
		}
	}
}

void TimeKeepingMode(struct tm* myTime){
	char buffer[80];

	system("clear");
//	time(timeinfo);

	myTime->tm_sec++;
	mktime(myTime);

	strftime(buffer, 80, "%a %Y-%m-%d \n %H:%M:%S \n", myTime);
	puts(buffer);

	//should get key inputs with multi-threads or asynchronously
	
	if(getch() == 'a'){
		printf("===== Time Setting ====== \n");
		TimeSetting(myTime);
	}
	
}

int main(){

	//for initializing current time data
	time_t timeinfo;
	struct tm* currentTime = malloc(sizeof(struct tm));

	time(&timeinfo);
	currentTime = localtime(&timeinfo);

	//initial time - set to 2019/01/01 00:00:00
	currentTime->tm_year = 2019 - 1900;
	currentTime->tm_mon = 1 - 1;
	currentTime->tm_mday = 1;
	currentTime->tm_hour = 0;
	currentTime->tm_min = 0;
	currentTime->tm_sec = 0;

	while(1){
		TimeKeepingMode(currentTime);
		sleep(1);
	}
}
