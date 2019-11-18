#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char getch(){
	char ch;
	ch = getchar();
	printf("%c \n", ch);
	return ch;
}

void displayTime(struct tm* alarmTime){
	char buffer[40];
	strftime(buffer, 80, "%H:%M \n", alarmTime);
	puts(buffer);
}

void AlarmOnOff(int* alarmOn) {
	*alarmOn = 1;
	//somehow passes this value to mode controller
	//In Time Keeping mode this value should be either accessible or should be passed
	//to the Time keeping mode or the mode controller
}

void AlarmTimeShift(int* select, char* opt[2]){
	*select = (*select + 1) % 2;
	printf("%s \n", opt[*select]);
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
	displayTime(alarmTime);
}

void AlarmSetting(struct tm* alarmTime) {
	int select = 0;
	char* option[2] = {"hour", "min"};
	char ch;

	while(1){
		ch = getch();

		if(ch == 'a'){
			break;
		} else if(ch == 'b'){
			IncreaseAlarmTime(select, alarmTime);
		} else if(ch == 'c') {
			AlarmTimeShift(&select, option);
		}
	}
}

void AlarmMode (struct tm* alarmTime) {
	int alarmOn = 0; //Mode Controller must have control over this variable
	char buffer[40];
	char ch = getch();
	
    
	//if an alarm indicator is on then it displays "on" and works the other way too
	printf("Alarm");
	printf( alarmOn != 0 ? " On \n" : " Off \n");
	
	//displays the time given
	strftime(buffer, 80, "%H:%M \n", alarmTime);
	puts(buffer);

	if(ch == 'a'){
		printf("===== Alarm Setting ===== \n");
		AlarmSetting(alarmTime);
	} else if(ch == 'b') {
		AlarmOnOff(&select);
	}
}

int main(){
	time_t timeinfo;
	struct tm* alarmTime;

	time(&timeinfo);
	alarmTime = localtime(&timeinfo);

	alarmTime->tm_hour = 12;
	alarmTime->tm_min = 0;

	while(1){
		AlarmMode(alarmTime);
		sleep(1);
	}
}


