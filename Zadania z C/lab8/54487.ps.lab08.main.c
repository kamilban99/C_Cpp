// PS IS1 322 LAB08
// Kamil Banaś
// bk54487@zut.edu.pl

#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>
#include <malloc.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>        
#include <fcntl.h>           
#include <string.h>
#include <crypt.h>

pthread_mutex_t fastMutex = PTHREAD_MUTEX_INITIALIZER;
char* content = NULL;
char salt[100] = "";
char* arg1 = NULL;
char* arg2 = NULL;
bool found = false;
bool optimal_threads = false;
int percent =  0;
char final_pwd[100] = "" ;

typedef struct{
	long start;
	long end;
}thread_arg;

void* thread_act(void *args){
	thread_arg* thread_args = (thread_arg*)args; 
	long start = thread_args->start;
	long end = thread_args->end;
	free(args);
	long current = start;
	char pwd[100] = "";
	int i = 0;
	struct crypt_data cd;
	bool local_found = false;
	while(current <= end && local_found == false){
		if(current % 100 == 0){
			pthread_mutex_lock( &fastMutex);
			local_found = found;
			pthread_mutex_unlock( &fastMutex);
		}

		while(content[current] != '\n'){
			pwd[i] = content[current];
			i++;
			current++;
		}
		pwd[i] = '\0';
		memset(&cd, 0, sizeof cd);
		crypt_r(pwd,salt,&cd);
		int result = strcmp(cd.output, arg1);
		if(result == 0){
			strncpy(final_pwd,pwd,100);
			pthread_mutex_lock( &fastMutex);
			found = true;
			local_found = found;
			pthread_mutex_unlock( &fastMutex);
		}
		memset(pwd,'\0',i+1);
		i = 0;
		if(start == 0 && !optimal_threads && current > 10){ //pierwszy wątek
			percent = 100 * current/end ;
			printf("\rPercentage status: %d %c", percent, '%');
			fflush(stdout);
		}
		current ++;
	}
}

int main(int argc, char *argv[]){
	arg1 = argv[1];
	arg2 = argv[2];
	int licz = 0, i = 0,j = 0;
	while(licz < 3){
		if(arg1[i] == '$') licz ++;
		salt[i] = arg1[i];
		i++;
	}
	salt[i] = '\0';
	int fd = open(argv[2], O_RDONLY | O_CREAT);
	long int size = lseek(fd, 0, SEEK_END);
	content = mmap(NULL, size, PROT_READ, MAP_SHARED,fd,0); //to jest teraz długi char!
	long processors = sysconf(_SC_NPROCESSORS_ONLN);
	long thread_id[processors];
	long int curr_start = 0, curr_end = 0;
	struct timespec start,finish;
	
	if(argc == 3){ //bez specyficznej ilosci watkow
		optimal_threads = true;
		for(int i = 1; i <= processors; i++){
			found = false;
			printf("number of threads: %d\n",i);
			curr_start = 0;
			clock_gettime(CLOCK_REALTIME, &start);
			for(int j = 1; j <= i; j++){
				curr_end = curr_start + size/i;
				while(content[curr_end]!= '\n' && curr_end < size) curr_end++;
				if(curr_end >= size)curr_end = size - 1;
				//printf("j = %d, start = %ld, end = %ld\n", j, curr_start, curr_end);
				pthread_t thread;
				thread_arg *args = malloc(sizeof(thread_arg));
				args->start = curr_start;
				args->end = curr_end;
				pthread_create(&thread, NULL, thread_act, args);
				thread_id[i] = thread;
				curr_start = curr_end + 1;
			}
			for(int j = 1; j <= i; j++){
				pthread_join(thread_id[j],NULL);
			}
			clock_gettime(CLOCK_REALTIME, &finish);
			long real_sec = 0; 
			long real_msec= 0;
			real_sec = finish.tv_sec - start.tv_sec;
			real_msec = (finish.tv_nsec - start.tv_nsec) / 1000000;
			if(real_msec < 0){
				real_sec -= 1;
				real_msec += 1000;
			}
			long total_time = real_msec + real_sec * 1000;
			printf("%d threads worked in total %ld ms.\n", i, total_time);	
		}
	}
	else{
		int threads_num = atoi(argv[3]);
		clock_gettime(CLOCK_REALTIME, &start);
		for(int j = 1; j <= threads_num; j++){
			curr_end = curr_start + size/threads_num;
			while(content[curr_end]!= '\n' && curr_end < size) curr_end++;
			if(curr_end >= size)curr_end = size - 1;
			printf("j = %d, start = %ld, end = %ld\n", j, curr_start, curr_end);
			pthread_t thread;
			thread_arg *args = malloc(sizeof(thread_arg));
			args->start = curr_start;
			args->end = curr_end;
			pthread_create(&thread, NULL, thread_act, args);
			thread_id[j] = thread;
			curr_start = curr_end + 1;
		}
		for(int j = 1; j <= threads_num; j++){
			pthread_join(thread_id[j],NULL);
		}
		clock_gettime(CLOCK_REALTIME, &finish);
		long real_sec = 0; 
		long real_msec= 0;
		real_sec = finish.tv_sec - start.tv_sec;
		real_msec = (finish.tv_nsec - start.tv_nsec) / 1000000;
		if(real_msec < 0){
			real_sec -= 1;
			real_msec += 1000;
		}
		long total_time = real_msec + real_sec * 1000;
		if(found)printf("\npassword was found! it was %s\n", final_pwd);
		else  printf("\npassword was not found...\n");
		printf("%d threads worked in total %ld ms.\n", threads_num, total_time);	
	}
	close(fd);
}
