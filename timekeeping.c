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


void displayTimeSetting(struct tm* myTime, int select){
        char* day[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };

        switch(select){
        case 0:
                        printf("%s %d-%02d-%02d \n %02d:%02d:\033[4m%02d\033[0m\n", day[myTime->tm_wday], myTime->tm_year + 1900, myTime->tm_mon + 1, myTime->tm_mday, myTime->tm_hour, myTime->tm_min, myTime->tm_sec);
                        break;
                case 1:
            printf("%s %d-%02d-%02d \n %02d:\033[4m%02d\033[0m:%02d\n", day[myTime->tm_wday], myTime->tm_year + 1900, myTime->tm_mon + 1, myTime->tm_mday, myTime->tm_hour, myTime->tm_min, myTime->tm_sec);
                        break;
                case 2:
                    printf("%s %d-%02d-%02d \n \033[4m%02d\033[0m:%02d:%02d\n", day[myTime->tm_wday], myTime->tm_year + 1900, myTime->tm_mon + 1, myTime->tm_mday, myTime->tm_hour, myTime->tm_min, myTime->tm_sec);
                        break;
                case 3:
                        printf("%s \033[4m%d\033[0m-%02d-%02d \n %02d:%02d:%02d\n", day[myTime->tm_wday], myTime->tm_year + 1900, myTime->tm_mon + 1, myTime->tm_mday, myTime->tm_hour, myTime->tm_min, myTime->tm_sec);
                        break;
                case 4:
                    printf("%s %d-\033[4m%02d\033[0m-%02d \n %02d:%02d:%02d\n", day[myTime->tm_wday], myTime->tm_year + 1900, myTime->tm_mon + 1, myTime->tm_mday, myTime->tm_hour, myTime->tm_min, myTime->tm_sec);
                        break;
                case 5:
                        printf("%s %d-%02d-\033[4m%02d\033[0m \n %02d:%02d:%02d\n", day[myTime->tm_wday], myTime->tm_year + 1900, myTime->tm_mon + 1, myTime->tm_mday, myTime->tm_hour, myTime->tm_min, myTime->tm_sec);
                        break;
                default:
                        printf("input error \n");
        }
}

void CurrentTimeShift(int* select){
	*select = (*select + 1) % 6;
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
}

void TimeSetting(struct tm* myTime){
	int select = 0;
	char ch;

	while(1){
		system("clear");
		printf("=====TIME SETTING=====\n");
		displayTimeSetting(myTime, select);
		ch = getch();
		
		if(ch == 'a'){
			break;
		} else if(ch == 'b') {
			IncreaseCurrentTime(select, myTime);
		} else if(ch == 'c') {
			CurrentTimeShift(&select);
		}
	}
}

void TimeKeepingMode(struct tm* myTime){
	system("clear");

	printf("=====CURRENT TIME=====\n");
	displayTime(myTime);
    
	//should get key inputs with multi-threads or asynchronously
	
	if(getch() == 'a'){
		TimeSetting(myTime);
	}

    myTime->tm_sec++;
	mktime(myTime);
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
