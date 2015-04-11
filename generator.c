#include "generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int get_random_suffix( char* ngram, ngrams_t* ngramsList ) 
{
    int randidx = -1;
    
    while( ngramsList != NULL )
    {
        printf( "funkcja get rand suf -> szukam indeksu\n" );
        if( (strcmp( ngram, ngramsList->nGram->ngram )) == 0 ) /*znalazl taki ngram w liscie*/
        {
		  		srand(time(NULL));
            randidx = ( int )( rand() / RAND_MAX ) * ( ngramsList->nGram->size );
            printf( "funkcja get rand suf -> znalazlem cos\n" );
				break;
        }
        else
            ngramsList = ngramsList->next;
    }
    return randidx;
}

void generate_text( wtab_t* wTab, ngrams_t* ngramsList, int howManyWords, int rank )
{
    ngram_t* nGram;
    char* newnGram;
	 char* sf;
    int randidx, counter, i = 0;
	 size_t fsize, ssize;
    
    nGram = make_ngram( rank, 0, wTab ); /*"losowy" pierwszy n-gram*/
    
    for( counter= 0; counter < howManyWords; )
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
            fprintf( stdout, "%s%s", nGram->ngram, ngramsList->sufTab->stab[randidx].suffix );
        }
        /*sf = strchr( nGram->ngram, ' ' );
        nGram->ngram = sf;
        nGram->ngram = strcat( nGram->ngram, ngramsList->sufTab->stab[randidx]->suffix );
        nGram->ngram = strcat( nGram->ngram, " " );*/
		  sf = strchr( nGram->ngram, ' ' );
		  fsize = strlen( nGram->ngram );
		  ssize = ngramsList->sufTab->stab[randidx].size;
		  newnGram = ( char* )malloc( (fsize+ssize) * sizeof (char) );

		  while( *sf != '\0' )
		  {
		  		newnGram[i] = (*sf);
				i++;
				sf++;
			}
		/*spr czy zmiesci sie sufiks -> napisac powiekszanie */
			nGram->ngram = strcat( nGram->ngram, newnGram );
			counter = (counter+1)*rank;
    }
	 printf( "\nKoniec tekstu.\n" );
    return;
}
