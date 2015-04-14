#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

list_t add_letter( list_t l, char c ) 
{
    elem_t* nl = ( elem_t* )malloc( sizeof *nl );
    if( l == NULL )
    {
        nl->letter = c;
        nl->next = NULL;
        l = nl;
        return l;
    }
    else
    {
        l->next = add_letter( l->next, c );
        return l;
    }
}

list_t get_letter( list_t l )
{
    if( l != NULL )
    {
        char c;
        c = l->letter;
        l = l->next;
        return l;
    }
}

void print_list( list_t l )
{
    elem_t *tmp = l;
    while(tmp != NULL)
    {
        printf( "%c->", tmp->letter );
        tmp = tmp->next;
    }
	 free(tmp);
    return;
}
