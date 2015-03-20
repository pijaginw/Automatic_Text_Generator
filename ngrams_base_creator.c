#include "ngrams_base_creator.h"
#include <stdio.h>
#include <string.h>

#define INIT_SIZE 3

char* make_ngram( int n, char** base ) 
{
    int index;
    int i;
    size_t size = INIT_SIZE;
    char* newNgram = 0;
    
    for( i= 0; i < n; i++ ) {
        newNgram = malloc( size * sizeof * newNgram );
        if( newNgram == NULL)
            fprintf( stderr, "\nBlad! Brak pamieci dla tablicy n-gramu\n" );
        else
            newNgram = strcat( newNgram, base[index] );
    }
    return newNgram;
}

ngram_t* make_base() {}

ngram_t* create_ngrams_base( char** base, ngram_t* list, int n, int baseSize ) 
{
    int idx = 0;
    int i;
    
    for( i= 0; i < baseSize-1; i++ )
    {
        list->ngram = make_ngram( n, base );
    }
    
    return list;
}

int get_ngram( ngram_t* list ) {}
