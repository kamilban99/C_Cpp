// PS IS1 322 LAB06
// Kamil Banaś
// bk54487@zut.edu.pl

void *mem_alloc(void *ptr, unsigned int size);
int mem_free (void *ptr);

typedef enum {
    NO_ERROR,
    M_ALLOCATION_FAILED,
    M_REALLOCATION_FAILED,
    M_POINTER_FAILED,
    M_NULL_POINTER
} Memory_error;
