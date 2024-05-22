// PS IS1 322 LAB06
// Kamil Banaś
// bk54487@zut.edu.pl

#include<stdio.h>
#include<unistd.h> 
#include<stdlib.h> 
#include"54487.ps.lab06.libmem.h"
#include<malloc.h>
#include<stdbool.h> 

typedef struct Node{
	void* ptr;
	unsigned int size;
	struct Node *next;
} Node;

const char *Errors[] = {
	"NO_ERROR",
    "M_ALLOCATION_FAILED",
    "M_REALLOCATION_FAILED",
    "M_POINTER_FAILED",
    "M_NULL_POINTER"
};

Memory_error err = NO_ERROR;
static int current_size = 0;
static Node* start = NULL;

void print_error(){ printf("%s\n",Errors[err]);}

void insert(Node** start, void* ptr, unsigned int size){
	Node* new = malloc(sizeof(Node));
	if(new == NULL){
		err = M_ALLOCATION_FAILED;
		print_error();
		return;
	}
	new->ptr = ptr;
	new->size = size;
	new->next = *start;
	*start = new;
}

bool delete(Node** start, void* ptr){
	Node* prev = NULL;
	Node* curr = *start;
	while(curr != NULL){
		//printf("%p %p\n", curr->ptr, ptr);
		if(curr->ptr == ptr){
			if(prev == NULL){ //pierwszy element
				*start = curr->next;
				}
			else{
				prev->next = curr->next;
			}
			free(curr->ptr);
			free(curr);
			return true;
		}
	 	prev = curr;
        curr = curr->next;
	}
	return false;
}

void free_all(){
	Node * curr = start;
	while(curr != NULL)
		delete(&curr, curr->ptr);
	start = NULL;
	current_size = 0;
}


void *mem_alloc(void *ptr, unsigned int size){
	void *new_memory = NULL;
	if(ptr != NULL){
		bool taken = false;
		Node* curr = start;
		
		while(curr != NULL){
			//printf("%p %p\n", curr->ptr, ptr);
			if(curr->ptr == ptr){
				taken = true;
				new_memory = realloc(ptr,size);
				if (new_memory == NULL) {
                	err = M_REALLOCATION_FAILED;
                	print_error();
                	return NULL;
                }
				curr->ptr = new_memory;
				curr->size = size;
				break;
			}
			curr = curr->next;
		}
		
		if(!taken){
			err = M_REALLOCATION_FAILED;
			print_error();
			return NULL;
		}
	}
	else{
		new_memory = calloc(1, size);
		if(new_memory == NULL){
			err = M_ALLOCATION_FAILED;
			print_error();
			return NULL;
		}
		insert(&start, new_memory, size);
		void *curr_memory = start->ptr;
		//printf("%p %p\n", new_memory, curr_memory);
		current_size++;
	}
	return new_memory;
}

int mem_free(void *ptr){
	if(ptr == NULL){
		err = M_NULL_POINTER;
		print_error();
		return -1;
	}
	bool taken = delete(&start,ptr);
	if(!taken){
		err = M_POINTER_FAILED;
		print_error();
		return -1;
	}
	else current_size--;	
	return 0;
}
void __attribute__((destructor)) free_all();
