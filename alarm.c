#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int alarmOn = 0;

char getch(){
	char ch;
	ch = getchar();
	printf("%c \n", ch);
	return ch;
}

void displayAlarm(struct tm* alarmTime){
	char buffer[40];	
	printf( alarmOn != 0 ? " On \n" : " Off \n");
	strftime(buffer, 80, "%H:%M \n", alarmTime);
	puts(buffer);
}

void displayAlarmSetting(struct tm* alarmTime, int select){
	switch(select){
		case 0:
			printf("\033[4m%02d\033[0m:%02d\n", alarmTime->tm_hour, alarmTime->tm_min);
			break;
		case 1:
			printf("%02d:\033[4m%02d\033[0m\n", alarmTime->tm_hour, alarmTime->tm_min);
			break;
		default:
			printf("input error \n");
	}
}

void AlarmOnOff() {
	alarmOn = !alarmOn;
	//somehow passes this value to mode controller
	//In Time Keeping mode this value should be either accessible or should be passed
	//to the Time keeping mode or the mode controller
}

void AlarmTimeShift(int* select){
	*select = (*select + 1) % 2;
}

void IncreaseAlarmTime(int select, struct tm* alarmTime){
	 switch(select){
        case 0:
            alarmTime->tm_hour++;
            break;
        case 1:
            alarmTime->tm_min++;
            break;
		default:
			printf("input error \n");
	 }

	//updates value
	mktime(alarmTime);
}

void AlarmSetting(struct tm* alarmTime) {
	int select = 0;

	char ch;

	while(1){
		system("clear");
		printf("=====ALARM SETTING=====\n");
		displayAlarmSetting(alarmTime, select);
		ch = getch();

		if(ch == 'a'){
			break;
		} else if(ch == 'b'){
			IncreaseAlarmTime(select, alarmTime);
		} else if(ch == 'c') {
			AlarmTimeShift(&select);
		}
	}
}

void AlarmMode (struct tm* alarmTime) {
	char ch;
    
	system("clear");
	printf("=====ALARM TIME=====\n");
	//if an alarm indicator is on then it displays "on" and works the other way too
	printf("Alarm");
		
	//displays the time given
	displayAlarm(alarmTime);

	ch = getch();

	if(ch == 'a'){
		AlarmSetting(alarmTime);
	} else if(ch == 'b') {
		AlarmOnOff();
	}
}

int main(){
	struct tm* alarmTime = malloc(sizeof(struct tm));

	memset(alarmTime, 0, sizeof(struct tm));

	while(1){
		AlarmMode(alarmTime);
		sleep(1);
	}
}


