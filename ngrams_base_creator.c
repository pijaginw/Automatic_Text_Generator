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

suftab_t* resize_suf_tab( suftab_t* sufTab )
{
    suftab_t* nst = realloc( sufTab->stab, 2 * (sufTab->capacity) * sizeof (char) );
    if( nst == NULL )
        fprintf( stderr, "\nBlad! Brak pamieci dla struktury tablicy sufiksow!\n" );
    nst->capacity *= 2;
    nst = sufTab;
    return nst;
}

suf_t* resize_suf( suf_t* s )
{
    suf_t* ns;
    ns->suffix = realloc( s->suffix, 2 * (s->capacity) * sizeof (char) );
    if( (ns->suffix) == NULL )
        fprintf( stderr, "\nBlad! Brak pamieci dla sufiksu!\n" );
    ns->capacity *= 2;
    s = ns;
    return s;
}

ngram_t* make_ngram( int rank, int idx, wtab_t* wTab ) 
{
    int i;
    size_t capacity = INIT_SIZE;
    
    ngram_t* newNgram = malloc( sizeof * newNgram );
    if( newNgram == NULL)
        fprintf( stderr, "\nBlad! Brak pamieci dla tablicy n-gramu\n" );
    
    newNgram->ngram = ( char* )malloc( capacity * sizeof (char) );
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
    int i, idx = 0;
    int true;
    ngram_t* newnGram;
    ngrams_t* ngramsList = NULL;
    ngrams_t* ntmp;
    ngrams_t* newEl;
    
    for( idx= 0; idx < wTab->size-rank; idx++ ) 
    {
        printf("jestem w for\n");
        true = 0;
        newnGram = make_ngram( rank, idx, wTab );
        while( ngramsList != NULL )
        {
            ngrams_t* tmp = ngramsList;
            if( (strcmp( newnGram->ngram, ngramsList->nGram->ngram )) == 0 )
            {
                printf("jestem w 1 if\n");
                true = 1;
                ngramsList->nGram->ngramCount++;
                if( (ngramsList->sufTab->size) == (ngramsList->sufTab->capacity) )
                    ngramsList->sufTab = resize_suf_tab( ngramsList->sufTab );
                if( (strlen( wTab->wordsTab[idx++]->word )) > ngramsList->sufTab->stab[ngramsList->sufTab->size]->size )
                    ngramsList->sufTab->stab[ngramsList->sufTab->size] = resize_suf( ngramsList->sufTab->stab[ngramsList->sufTab->size] );
                idx--;
                ngramsList->sufTab->stab[ngramsList->sufTab->size++]->suffix = wTab->wordsTab[idx++]->word;
                idx--;
                printf("jestem przed break\n");
                break;
            }
            tmp = ngramsList->next;
        }
        
        if( true == 0 )
        {
        newEl = ( ngrams_t* )malloc( sizeof * newEl );
        if( newEl == NULL)
            fprintf( stderr, "\nBlad! Brak pamieci dla nowego elementu listy n-gramow!\n" );
        
        newEl->nGram = newnGram;
        newEl->nGram->ngramCount++;
        newEl->sufTab = init_suf_tab();
        newEl->sufTab->stab[newEl->sufTab->size++]->suffix = wTab->wordsTab[idx++]->word;
        idx--;
        newEl->next = ngramsList;
        printf("jestem po newEl\n");
        }
    }
    return newEl;
}

void print_ngramsList( ngrams_t* ngramsList )
{
    int i;
    printf( "\n\ntest tworzenia listy ngramow:\n" );
    while( ngramsList != NULL )
    {
        printf( "ngram:%s\n", ngramsList->nGram->ngram );
        printf( "sufiks:%s\n", ngramsList->sufTab->stab[0] );
        ngramsList = ngramsList->next;
    }
}

char* get_ngram( ngrams_t* list ) 
{
    char* ngram;
    
    if( list != NULL )
        ngram = list->nGram->ngram;
    
    return ngram;
}
