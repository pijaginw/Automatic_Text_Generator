#include "stack.h"
#include <stdio.h>

list_t init_list()
{
    elem_t *nw = malloc( sizeof *nw );
    if( nw == NULL )
    {
        printf( "\nBlad! Brak pamieci dla listy.\n" );
        return NULL;
    }
    nw->letter = 0;
    nw->next = NULL;
    return nw;
}

list_t add_letter( list_t l, char c ) 
{
    elem_t *nl = malloc( sizeof *nl );
    if( l == NULL )
    {
        nl->letter = c;
        nl->next = NULL;
        return nl;
    }
    else
    {
        l->next = add_letter( l->next, c );
        return l;
    }
}

char get_letter( list_t l )
{
    char c;
    if( l != NULL )
    {
        c = l->letter;
        l = l->next;
        return c;
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
    return;
}