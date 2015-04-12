#include "generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int get_random_suffix( int index, nbtab_t* ngramsBase ) 
{
	/* index to indeks ngramu w bazie n-gramow, dla ktorego chce znalezc sufiks */
    int randidx = -1;

   	printf( "funkcja get rand suf -> szukam indeksu\n" );
		  	
		srand(time(NULL));
      randidx = ( int )( rand()/RAND_MAX ) * ( ngramsBase->ngramsBaseTab[index].sufTab->size );
      printf( "funkcja get rand suf -> znalazlem cos\n" );

   return randidx;
}

void generate_text( wtab_t* wTab, nbtab_t* ngramsBase, int howManyWords, int rank )
{
    ngram_t* nGram;
    ngram_t* newnGram;
	 char* sf, *pt = NULL;
    int randidx, counter, i = 0, cnt = 0;
	 size_t ssize, idx;
    
    nGram = make_ngram2( wTab, 0, rank ); /*"losowy" pierwszy n-gram*/
    
    for( counter= 0; counter < howManyWords; )
    {
	 	for( idx= 0; idx < ngramsBase->size; idx++ )
		{
			if( (strcmp( nGram->ngram, ngramsBase->ngramsBaseTab[idx].nGram->ngram )) == 0 )
			{
				/* znalazl taki n-gram w bazie ngramow */
        		randidx = get_random_suffix( idx, ngramsBase );
        		printf( "wylosowany indeks:%d\n", randidx );
        		if( randidx == -1 )
        		{
            	fprintf( stdout, "Nie znaleziono n-gramu. Koniec generowania tekstu.\n" );
            	return;
        		}
        		else
        		{
					/* tworzenie nowego n-gramu */
					printf( "czy tworze ngram??\n" );
            	printf( "%s%s\n", nGram->ngram, wTab->wordsTab[ngramsBase->ngramsBaseTab[idx].sufTab->suffixes[randidx]]->word );
        			
					sf = strchr( nGram->ngram, ' ' );
					while( (*sf++) != '\0' ) {
						printf( "-->znak*%c*\n", *sf );
						cnt++;
					}
					printf( "ile znakow zostalo w ngramie:%d\n", cnt );

					ssize = strlen( wTab->wordsTab[ngramsBase->ngramsBaseTab[idx].sufTab->suffixes[randidx]]->word );
					
					newnGram = ( ngram_t* )malloc( sizeof * newnGram );
					if( newnGram == NULL )
						fprintf( stderr, "\nBlad! Nie przyznano pamieci dla struktury nowego n-gramu.\n" );

					newnGram->ngram = ( char* )malloc( (ssize + cnt + 1) * sizeof (char ) );
					if( (newnGram->ngram) == NULL )
						fprintf( stderr, "\nBlad! Nie przydzielono pamieci dla nowego n-gramu.\n" );

					for( pt= sf; *pt != '\0'; pt++ ) /*kopiuje reszte starego n-gramu do nowego n-gramu */
						newnGram->ngram[i++] = *pt;
					printf( "przeksztalcanie newnGram:%s\n", newnGram->ngram );

					newnGram->ngram = strcat( newnGram->ngram, wTab->wordsTab[ngramsBase->ngramsBaseTab[idx].sufTab->suffixes[randidx]]->word );
					newnGram->ngram = strcat( newnGram->ngram, " " );
					printf( "przeksztalcanie dalsze newnGram:%s\n", newnGram->ngram );

					nGram->ngram = ( char* )malloc( (strlen( newnGram->ngram ) + 1) * sizeof (char) );
					if( (nGram->ngram) == NULL )
						fprintf( stderr, "\nBlad! Nie przydzielono miejsca dla nowego n-gramu w starym n-gramie.\n" );
					nGram->ngram = ( char* )memset( nGram->ngram, '\0', strlen( newnGram->ngram ) + 1 );

					nGram = newnGram;
				}
				counter += rank;
				break;
			}
		}
    }
	 printf( "\nKoniec tekstu.\n" );
    return;
}
