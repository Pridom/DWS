#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <term.h>
#include <termios.h>

int alarmOn=0;
char inputData;
int ModeData=1;
//1 TimeKeeping 2 TimeSetting 3 Alarm 4 AlarmSetting 5 StopWatch 6 StopWatch
struct tm* alarmTime;
struct tm* currentTime;

struct StopWatch {
	int min;
	int sec;
	int micsec;

	int t_m;
	int t_s;
	int t_ms;

	int keepgoing;
};


char c_input(void) {
	char ch;
	char inputch;
	int cnt = 0;
	double result;
	struct termios buf;
	struct termios save;
	int first = 0;
	tcgetattr(0, &save);
	buf = save;
	buf.c_lflag &= ~(ICANON | ECHO);
	buf.c_cc[VMIN] = 1;
	buf.c_cc[VTIME] = 0;
	tcsetattr(0, TCSAFLUSH, &buf);
	clock_t start;
	ch = getchar();
	inputch=ch;
	inputData = ch;
	tcsetattr(0, TCSAFLUSH, &save);
	return inputch;
}

void displayTime(){
	printf("Alarm");
	printf( alarmOn != 0 ? " On \n" : " Off \n");
	char buffer[80];
	strftime(buffer, 80, "%a %Y-%m-%d \n %H:%M:%S \n", currentTime);
	puts(buffer);
}

void displayTimeSetting( int select){
	char* day[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };

	switch(select){
	case 0:
		printf("%s %d-%02d-%02d \n %02d:%02d:\033[4m%02d\033[0m\n", day[currentTime->tm_wday], currentTime->tm_year + 1900, currentTime->tm_mon + 1, currentTime->tm_mday, currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec);
		break;
	case 1:
		printf("%s %d-%02d-%02d \n \033[4m%02d\033[0m:%02d:%02d\n",day[currentTime->tm_wday], currentTime->tm_year + 1900, currentTime->tm_mon + 1, currentTime->tm_mday, currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec);
		break;
	case 2:
		printf("%s %d-%02d-%02d \n %02d:\033[4m%02d\033[0m:%02d\n",day[currentTime->tm_wday], currentTime->tm_year + 1900, currentTime->tm_mon + 1, currentTime->tm_mday, currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec);
		break;
	case 3:
		printf("%s \033[4m%d\033[0m-%02d-%02d \n %02d:%02d:%02d\n",day[currentTime->tm_wday], currentTime->tm_year + 1900, currentTime->tm_mon + 1, currentTime->tm_mday, currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec);
		break;
	case 4:
		printf("%s %d-\033[4m%02d\033[0m-%02d \n %02d:%02d:%02d\n", day[currentTime->tm_wday], currentTime->tm_year + 1900, currentTime->tm_mon + 1, currentTime->tm_mday, currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec);
		break;
	case 5:
		printf("%s %d-%02d-\033[4m%02d\033[0m \n %02d:%02d:%02d\n",day[currentTime->tm_wday], currentTime->tm_year + 1900, currentTime->tm_mon + 1, currentTime->tm_mday, currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec);
		break;
	default:
		printf("input error \n");
	}
}

void CurrentTimeShift(int* select){
	*select = (*select + 1) % 6;
}

void IncreaseCurrentTime(int select){
	switch(select){
		case 0:
			currentTime->tm_sec++;
			break;
		case 1:
			currentTime->tm_hour++;
			break;
		case 2:
			currentTime->tm_min++;
			break;
		case 3:
			currentTime->tm_year++;
			break;
		case 4:
			currentTime->tm_mon++;
			break;
		case 5:
			currentTime->tm_mday++;
			break;
		default:
			printf("input error \n");
	}

	mktime(currentTime);
}

void TimeSetting(){
	int select = 0;

	system("clear");
	printf("=====TIME SETTING=====\n");
	displayTimeSetting( select);

	while(1){
		usleep(50000);
		if(ModeData != 10){
			system("clear");
			printf("=====TIME SETTING=====\n");
			displayTimeSetting(select);
			if(inputData == 'a'){
				inputData=' ';
				break;
			} else if(inputData == 'b') {
				inputData=' ';
				IncreaseCurrentTime(select);
			} else if(inputData == 'c') {
				inputData=' ';
				CurrentTimeShift(&select);
			}
		}
		usleep(50000);
	}
}

void TimeKeepingMode(){
	while(1){
		if(ModeData == 1){
			system("clear");

			printf("=====CURRENT TIME=====\n");
			displayTime();
    
			//should get key inputs with multi-threads or asynchronously
		
			if(ModeData != 10 && inputData == 'a'){
				inputData=' ';
				TimeSetting();
			}
			else if(ModeData != 10 && inputData == 'c'){
				inputData=' ';
				ModeData=3;
			}
		
		}
		currentTime->tm_sec++;
		mktime(currentTime);
		sleep(1);
	}
}

void displayAlarm(){
	char buffer[40];	
	printf( alarmOn != 0 ? " On \n" : " Off \n");
	strftime(buffer, 80, "%H:%M \n", alarmTime);
	puts(buffer);
}

void displayAlarmSetting(int select){
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

void IncreaseAlarmTime(int select){

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

void AlarmSetting() {
	int select = 0;
	
	system("clear");
	printf("=====ALARM SETTING=====\n");
	displayAlarmSetting(select);

	while(1){
		usleep(50000);
		if(ModeData != 10){
			system("clear");
			printf("=====ALARM SETTING=====\n");
			displayAlarmSetting(select);
			if(ModeData!=10&&inputData == 'a'){
				inputData=' ';
				break;
			} else if(ModeData!=10&&inputData == 'b'){
				inputData=' ';
				IncreaseAlarmTime(select);
			} else if(ModeData!=10&&inputData == 'c') {
				inputData=' ';
				AlarmTimeShift(&select);
			}
		}
		usleep(50000);
	}
	
}
void AlarmMode() {
	while(1) {
		usleep(50000);
		if(ModeData==3) {
    
			system("clear");
			printf("=====ALARM TIME=====\n");
			//if an alarm indicator is on then it displays "on" and works the other way too
			printf("Alarm");
		
			//displays the time given
			displayAlarm();


			if(ModeData!=10&&inputData == 'a') {
				inputData=' ';
				AlarmSetting();
			} else if(ModeData!=10&&inputData == 'b') {
				inputData= ' ';
				AlarmOnOff();
			}else if(ModeData!=10&&inputData=='c') {
				inputData=' ';
				ModeData=5;
			}
		}
		usleep(50000);
	}
}

void display(struct StopWatch* sw) {
	while (1) {
		usleep(50000);
		//system("clear");
		if (ModeData==5) {
			system("clear");
			printf("  Record  %d  %d\n", currentTime->tm_hour, currentTime->tm_min);
			printf("  %d' %d\" %d\n", sw->min, sw->sec, sw->micsec);
		}
		else if (ModeData==6) {
			system("clear");
			printf("  Lap     %d  %d\n", currentTime->tm_hour, currentTime->tm_min);
			printf("  %d' %d\" %d\n", sw->t_m, sw->t_s, sw->t_ms);
		}
		usleep(50000);
	}
}

void increase_stopwatch_time(struct StopWatch* sw) {
	while (1) {
		if (sw->keepgoing == 1) {
			if (sw->micsec == 99) {
				sw->micsec = 0;//increase sec

				if (sw->sec == 59) {
					sw->sec = 0;//increase min

					if (sw->min == 9) {
						sw->min = 0;
					}
					else if (sw->min >= 0 && sw->min < 9) {
						sw->min += 1;
					}
					else {
						printf("Stopwatch's minute has Overflow or Underflow!!!!!!!!!!");
						exit(9);
					}

				}
				else if (sw->sec >= 0 && sw->sec < 59) {
					sw->sec += 1;
				}
				else {
					printf("Stopwatch's second has Overflow or Underflow!!!!!!!!!!");
					exit(59);
				}

			}
			else if (sw->micsec >= 0 && sw->micsec < 99) {
				sw->micsec += 1;
			}
			else {
				printf("Stopwatch's micro second has Overflow or Underflow!!!!!!!!!!");
				exit(99);
			}
		}
		usleep(10000);
	}
}

void Stopwatch_Controller(struct StopWatch* sw) {
	while (1) {
		if (ModeData == 5) {
			inputData= ' ';
			usleep(2);
			if (ModeData!=10&&inputData == 'b' && sw->keepgoing == 0) {
				inputData =' ';
				sw->keepgoing = 1;
				continue;
			}
			else if (ModeData!=10&&inputData == 'b' && sw->keepgoing == 1) {
				sw->keepgoing = 0;
				inputData = ' ';
				continue;
			}
			else if (ModeData!=10&&inputData == 'a' && sw->keepgoing == 1) {
				sw->t_m = sw->min;
				sw->t_s = sw->sec;
				sw->t_ms = sw->micsec;
				ModeData = 6;
				inputData = ' ';
			}
			else if (ModeData!=10&&inputData == 'a' && sw->keepgoing == 0) {
				sw->min = 0;
				sw->sec = 0;
				sw->micsec = 0;
				sw->t_m = 0;
				sw->t_s = 0;
				sw->t_ms = 0;
				inputData = ' ';
				continue;
			}
			else if (ModeData!=10&&inputData == 'c') {
				inputData= ' ';
				ModeData=1;
			}
		}else if(ModeData==6){
			//usleep(2);
			if (ModeData!=10&&inputData == 'b') {
				ModeData = 5;
				inputData = ' ';
			}
			else if (ModeData!=10&&inputData == 'a') {
				sw->t_m = sw->min;
				sw->t_s = sw->sec;
				sw->t_ms = sw->micsec;
				inputData = ' ';
			}
			else if (ModeData != 10 && inputData == 'c') {
				inputData = ' ';
				ModeData = 1;
			}
		}
		
	}
}
void *t_function() {
	while (1) {
		inputData = c_input();
		printf("%c", inputData);
	}
}
int compare() {
	return (currentTime->tm_hour == alarmTime->tm_hour) && (currentTime->tm_min == alarmTime->tm_min);
}

void alarming() {
    int i = 0;
	int temp;
    while(1){
	
    	if(compare() && alarmOn&&currentTime->tm_sec==0){
		temp=ModeData;
		ModeData=10;//State = Alarming
        	for(i = 0; i < 5; i++){
			system("clear");
           		printf("=====ALARMING=====\a\n");
           		printf("=====CURRENT TIME=====\n");
           		displayTime();
           		printf("=====ALARM TIME=====\n");
           		displayAlarm();
           		sleep(1);
				if(inputData=='a'||inputData=='b'||inputData=='c'||inputData=='d'){
					inputData=' ';
					break;
				}
        	}
		ModeData=temp;
    	}
    }
}

void BackLight(){
	while(1){
		if(!alarmOn||!compare()){
			if(inputData=='d'){
				inputData=' ';
				printf("%c[1;33m",27);
				sleep(2);
				printf("%c[0m\n",27);
			}
		}
	}
}
void main() {
	alarmTime = malloc(sizeof(struct tm));

	memset(alarmTime, 0, sizeof(struct tm));
	//time_t timeinfo 변수는 맨-처음 시간 초기화해줄떄만 필요하고 그 외엔 필요 X
	time_t timeinfo;
	//현재 시간은 무조건 동적할당으로 초기화 해줘야한다
	currentTime = malloc(sizeof(struct tm));
      
	//struct tm* currentTime 초기화해주는 부분
	time(&timeinfo);
	currentTime = localtime(&timeinfo);

	//초기 설정 시간은 2019년 1월 1일 00시 00분 00초
	currentTime->tm_year = 2019 - 1900;
	currentTime->tm_mon = 1 - 1;
	currentTime->tm_mday = 1;
	currentTime->tm_hour = 0;
	currentTime->tm_min = 0;
	currentTime->tm_sec = 0;
	pthread_t p_thread[10];
	int thr_id[10];
	
	struct StopWatch* sw = malloc(sizeof(struct StopWatch));

	sw->min = 0;
	sw->sec = 0;
	sw->micsec = 0;
	sw->keepgoing = 0;

	thr_id[5] = pthread_create(&p_thread[5], NULL, AlarmMode,NULL);
	thr_id[4] = pthread_create(&p_thread[4], NULL, TimeKeepingMode,NULL);
	thr_id[2] = pthread_create(&p_thread[2], NULL, display, (void *)sw);
	thr_id[1] = pthread_create(&p_thread[1], NULL, increase_stopwatch_time, (void *)sw);
	thr_id[0] = pthread_create(&p_thread[0], NULL, t_function, NULL);
	thr_id[3] = pthread_create(&p_thread[3], NULL, BackLight, NULL);
	thr_id[6] = pthread_create(&p_thread[6], NULL, Stopwatch_Controller,(void *)sw);
	thr_id[7] = pthread_create(&p_thread[7], NULL, alarming,NULL);
	while (1) {
		
	}
}