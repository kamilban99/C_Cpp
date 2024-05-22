// PS IS1 322 LAB07
// Kamil Banaś
// bk54487@zut.edu.pl

#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>
#include "54487.ps.lab07.timer.h"
#include <malloc.h>
#include <signal.h>
#include <stdbool.h>

int max_time = 0, n_threads = 0, opt;
pthread_t loop;
pthread_mutex_t fastMutex=PTHREAD_MUTEX_INITIALIZER;

typedef struct Data_thread{
   int timer;
   long tid;
}Data_thread;

void handler(int n, siginfo_t *info, void * u){
	pthread_mutex_lock( &fastMutex);
	loop = pthread_self();
}

void* thread_act(){
	int c = 1;
	struct sigaction sig;
	sig.sa_sigaction = handler;
	sigemptyset(&(sig.sa_mask));
	sig.sa_flags = SA_SIGINFO;
	sigaction(SIGALRM, &sig, NULL);
	start();
	while (loop != pthread_self()){
		c++;
		c--;
	}
	pthread_mutex_unlock(&fastMutex);

	long total_time = end();
	char str[] = "Thread";
	printf("%40s %ld, time elapsed %ld ms\n", str, pthread_self(), total_time);
	return NULL;
}


int main(int argc, char *argv[]){
	while ((opt = getopt (argc, argv, "m:n:")) != -1)
		switch (opt) {
			case 'm': max_time = atoi(optarg); break;
			case 'n': n_threads = atoi(optarg); break;
			case '?':
				fprintf(stderr, "Unknown option -%c\n", optopt);
				return 1;
			default: abort();
		}
	Data_thread *threads[n_threads];
	
	for(int i = 0; i <  n_threads; i++){
		srand(time(0)+i);
		threads[i] = malloc(sizeof(Data_thread));
		int timer = 1 + rand() / (RAND_MAX / (max_time) + 1);
		pthread_t thread;
		pthread_create(&thread, NULL, thread_act,NULL);
		printf("Thread %ld lives %d sec\n", thread, timer);
		threads[i]->timer = timer;
		threads[i]->tid = thread;
	}
	for(int i = 1; i <= max_time; i++){
		sleep(1);
		for(int j = 0; j < n_threads; j++){
			if(threads[j]->timer == i)
				pthread_kill(threads[j]->tid,SIGALRM);		
		}
	}
	sleep(1);
	for(int i = 0; i < n_threads; i++){
		pthread_join(threads[i]->tid,NULL);
		free(threads[i]);	
	}
	pthread_mutex_destroy(&fastMutex);
	return 0;
}
