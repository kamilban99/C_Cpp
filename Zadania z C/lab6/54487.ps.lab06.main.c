// PS IS1 322 LAB06
// Kamil Banaś
// bk54487@zut.edu.pl

#include<stdio.h>
#include<unistd.h> 
#include<stdlib.h> 
#include"54487.ps.lab06.libmem.h"
#include<malloc.h>

int main(int argc, char *argv[]){
	printf("Welcome to memory manager\n");
	printf("1st alloc\n");
	void *mem1 = mem_alloc(NULL, 5);
	printf("2nd alloc\n");
	void *mem2 = mem_alloc(NULL, 3);
	printf("3rd alloc\n");
	void *mem3 = mem_alloc(NULL, 10);

	printf("1st free\n");
	int free1 = mem_free(mem1);
	printf("2nd free\n");
	int free2 = mem_free(mem1);
	
	printf("1st realloc\n");
	void *mem4 = mem_alloc(mem2, 4);
	printf("2nd realloc\n");
	void *mem5 = mem_alloc(mem1, 6);
	
	return 0;
}
