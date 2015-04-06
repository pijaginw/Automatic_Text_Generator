#include "generator.h"
#include <stdio.h>
#include <stdlib.h>

int get_random_suffix( char* ngram, ngrams_t* ngramsList ) 
{
    int randidx = -1;
    
    while( ngramsList != NULL )
    {
        if( (strcmp( ngram, ngramsList->nGram->ngram )) == 0 ) /*znalazl taki ngram w liscie*/
        {
            randidx = (0 + ngramsList->sufTab->size) * rand() / RAND_MAX;
        }
        else
            ngramsList = ngramsList->next;
    }
    
    return randidx;
}
