// PS IS1 322 LAB07
// Kamil Banaś
// bk54487@zut.edu.pl

#include<stdio.h>
#include<unistd.h> 
#include<stdlib.h> 
#include"54487.ps.lab07.timer.h"
#include<malloc.h>
#include<stdbool.h>
#include <sys/times.h>
#include <time.h>
#include <pthread.h>
#include <signal.h>

typedef struct Data{
	int tick;
	struct timespec start;
} Data;

static pthread_key_t counterKey;
static pthread_once_t counterOnce = PTHREAD_ONCE_INIT;
static void freeMemory(void *buffer){ 
	free(buffer);
}
static void createKey(void){
	pthread_key_create(&counterKey, freeMemory);
}

Data *getTick(){
	Data *data;
	pthread_once(&counterOnce, createKey);
	data = pthread_getspecific(counterKey);
	if (data == NULL){
		data = malloc(sizeof(Data));
		if(data == NULL){
			fprintf(stderr, "malloc failed\n");
			return NULL;
		}
		data->tick =  0;
		pthread_setspecific(counterKey, data);
	}
	data->tick++;
	return data;
}

void start(){
	struct timespec start;
	clock_gettime(CLOCK_REALTIME, &start);
	Data *data = getTick();
	if(data == NULL){
		fprintf(stderr, "getTick failed\n");
		return;
	}
	data->start = start;
}

long end(){
	long real_sec = 0; 
	long real_msec= 0;
	struct timespec start, finish;
	clock_gettime(CLOCK_REALTIME, &finish);
	Data *data = getTick();
	if(data == NULL){
		fprintf(stderr, "getTick failed\n");
		return -1;
	}
	start = data->start;
	real_sec = finish.tv_sec - start.tv_sec;
	real_msec = (finish.tv_nsec - start.tv_nsec) / 1000000;
	if(real_msec < 0){
		real_sec -= 1;
		real_msec += 1000;
	}
	long total_time = real_msec + real_sec * 1000;
	return total_time;
}
