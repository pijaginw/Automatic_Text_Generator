#ifndef _STACK_H_
#define	_STACK_H_

#define INIT_SIZE 5

#include <stdio.h>

typedef struct elem {
    char letter;
    struct elem *next;
} elem_t, *list_t;

list_t add_letter( list_t l, char c );
list_t get_letter( list_t l );
void print_list( list_t l );

#endif

