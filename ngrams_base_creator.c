#include "ngrams_base_creator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* !!
 * dodać generowanie pliku bazowego z n-gramami 
 * !!! */

suftab_t* init_suf_tab() 
{
    int i;
    suftab_t* nsf = malloc( sizeof * nsf );
    if( nsf == NULL )
        fprintf( stderr, "\nBlad! Brak pamieci dla struktury tablicy sufiksów!\n" );
    nsf->stab = malloc( INIT_SIZE * sizeof * *(nsf->stab) );
    if( (nsf->stab) == NULL )
        fprintf( stderr, "\nBlad! Brak pamieci dla tablicy sufiksów!\n" );
    for( i= 0; i < INIT_SIZE; i++)
        nsf->stab[i] = init_suf();
    nsf->size = 0;
    nsf->capacity = INIT_SIZE;
    return nsf;
}

suf_t* init_suf()
{
    suf_t* ns = ( suf_t* )malloc( sizeof * ns );
    if( ns == NULL )
        fprintf( stderr, "\nBlad! Brak pamieci dla struktury sufiksu!\n" );
    
    ns->suffix = ( char* )malloc( INIT_SIZE * sizeof (char) );
    if( (ns->suffix) == NULL )
        fprintf( stderr, "\nBlad! Brak pamieci dla sufiksu!\n" );
    
    ns->prob = 0;
    ns->size = 0;
    ns->capacity = INIT_SIZE;
    return ns;
}

ngram_t* make_ngram( int rank, int idx, wtab_t* wTab ) 
{
    int i;
    size_t capacity = INIT_SIZE;
    
    ngram_t* newNgram = malloc( sizeof * newNgram );
    if( newNgram == NULL)
        fprintf( stderr, "\nBlad! Brak pamieci dla tablicy n-gramu\n" );
    
    newNgram->ngram = malloc( capacity * sizeof (char) );
    if( (newNgram->ngram) == NULL)
        fprintf( stderr, "\nBlad! Brak pamieci dla n-gramu\n" );
    
    newNgram->capacity = capacity;
    newNgram->size = 0;
    newNgram->ngramCount = 0;
    
    for( i= 0; i < rank; i++ ) {
        if( (newNgram->size + wTab->wordsTab[idx]->size) > newNgram->capacity )
        {
            newNgram->ngram = realloc( newNgram->ngram, 2 * newNgram->capacity);
            newNgram->capacity *= 2;
        }
        newNgram->ngram = strcat( newNgram->ngram, wTab->wordsTab[idx++]->word );
        newNgram->ngram = strcat( newNgram->ngram, " " );

        newNgram->size = strlen( newNgram->ngram );
    }
    return newNgram;
}

ngrams_t* create_ngrams_base( wtab_t* wTab, int rank ) 
{
    int i;
    int idx = 0;
    ngrams_t* ngramsList = NULL;
    for( i= 0; i < wTab->size-rank+1; i++ ) 
    {
        ngrams_t* newEl = ( ngrams_t* )malloc( sizeof * newEl );
        if( newEl == NULL)
            fprintf( stderr, "\nBlad! Brak pamieci dla nowego elementu listy n-gramów\n" );
        
        newEl->nGram = make_ngram( rank, idx++, wTab );
        newEl->next = ngramsList;
    }
    return ngramsList;
}

char* get_ngram( ngrams_t* list ) 
{
    char* ngram;
    
    if( list != NULL )
        ngram = list->nGram->ngram;
    
    return ngram;
}
