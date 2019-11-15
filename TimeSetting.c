#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>


//gets the time and saves it into the struct tm
struct tm* setTime(time_t* timeinfo, struct tm* myTime){
	//temporary storage for time input
	int hour, min, sec, year, mon, day;
	printf("Hour - Min - Sec: ");
	scanf("%d %d %d", &hour, &min, &sec);
	fflush(stdin);
	printf("YYYY-MM-DD: ");
	scanf("%d %d %d", &year, &mon, &day);
	fflush(stdin);

	//saves given time into struct tm
	myTime->tm_year = year - 1900;
	myTime->tm_mon = mon - 1;
	myTime->tm_mday = day;
	myTime->tm_hour = hour;
	myTime->tm_min = min;
	myTime->tm_sec = sec;

	mktime(myTime);

	return myTime;
}

char getch(){
	char ch;
	ch = getchar();
	printf("%c \n", ch);
	return ch;
}


//displays the time based on the info in struct tm
void displayTime(time_t* timeinfo, struct tm* myTime){
	//temporary storage for saving the string to display the time
	char buffer[80];

	mktime(myTime);

	while(1){
		//clears the screen
		system("clear");
		getch();
		
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

void timeSetting(struct tm* myTime){
	char buffer[80];
	char ch;
	int sec, min, hour, year, mon, day = 0;
	int input[6] = {sec, min, hour, year, mon, day};
	char* inputDesc[6] = {"second", "minute", "hour", "year",
		                  "mon", "day"};

	int select = 0; //for choosing which element to be increased 

	mktime(myTime);
	while(1){
		system("clear");
		strftime(buffer, 80, "%a %Y-%m-%d \n %H:%M:%S \n", myTime);
		puts(buffer);

		printf("\n");
		printf("%s \n", inputDesc[select]);
		ch = getch();
	
		if(ch == 'c'){
			select = (select + 1) % 6;
		}

		if(ch == 'b'){
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
		}

		mktime(myTime);
	}
}
		

int main(){
	time_t timeinfo;
	struct tm* myTime = malloc(sizeof(struct tm));

	//initializes timeinfo and myTime
	time(&timeinfo);
	myTime = localtime(&timeinfo);

	setTime(&timeinfo, myTime);
//	displayTime(&timeinfo, myTime);

//	free(myTime);

	timeSetting(myTime);

	return 0;
}





