#include "generator.h"
#include <stdio.h>
#include <stdlib.h>

int get_random_suffix( char* ngram, ngrams_t* ngramsList ) 
{
    int randidx = -1;
    
    while( ngramsList != NULL )
    {
        printf( "funkcja get rand suf -> szukam indeksu\n" );
        if( (strcmp( ngram, ngramsList->nGram->ngram )) == 0 ) /*znalazl taki ngram w liscie*/
        {
            randidx = (0 + ngramsList->sufTab->size) * rand() / RAND_MAX;
            printf( "funkcja get rand suf -> znalazlem cos" );
        }
        else
            ngramsList = ngramsList->next;
    }
    return randidx;
}

void generate_text( wtab_t* wTab, ngrams_t* ngramsList, int howManyWords, int rank )
{
    ngram_t* nGram;
    char* sf;
    int randidx, counter;
    
    nGram = make_ngram( rank, 0, wTab ); /*"losowy" pierwszy n-gram*/
    
    for( counter= 0; counter < howManyWords; (counter++)*rank )
    {
        randidx = get_random_suffix( nGram->ngram, ngramsList );
        printf( "wylosowany indeks:%d\n", randidx );
        if( randidx == -1 )
        {
            fprintf( stdout, "Nie znaleziono n-gramu. Koniec generowania tekstu.\n" );
            return;
        }
        else
        {
            fprintf( stdout, "%s%s", nGram->ngram, ngramsList->sufTab->stab[randidx]->suffix );
        }
        sf = strchr( nGram->ngram, ' ' );
        nGram->ngram = sf;
        nGram->ngram = strcat( nGram->ngram, ngramsList->sufTab->stab[randidx]->suffix );
        nGram->ngram = strcat( nGram->ngram, " " );
    }
    return;
}
