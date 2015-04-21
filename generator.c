#include "generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int get_random_suffix( int index, nbtab_t* ngramsBase, int seed ) 
{
	/* index to indeks ngramu w bazie n-gramow, dla ktorego chce znalezc sufiks */
    int randidx = -1;
	 srand(seed);
	randidx = ( rand() % (ngramsBase->ngramsBaseTab[index].sufTab->size ) );

   return randidx;
}

void generate_text( wtab_t* wTab, nbtab_t* ngramsBase, int howManyWords, int par, int rank, int seed, char* outFileName )
{
    ngram_t* nGram;
    ngram_t* newnGram;
	 char* sf, *pt = NULL;
    int randidx, counter, i, cnt = 0, isfound = 0, randngram, fcheck = 0, parcnt = 1;
	 size_t ssize, idx;
	 double prob;
	 
	 FILE* outfile = fopen( outFileName, "w" );
	
	srand(time(NULL));
	 randngram = ( rand() % (ngramsBase->size-rank) );
	nGram = make_ngram2( wTab, randngram, rank ); /* losowy pierwszy n-gram */
	
	fprintf( outfile, "%s", nGram->ngram );

    for( counter= rank; counter < howManyWords; )
    {
	 	isfound = 0;
		if( (counter == ((howManyWords/par)*parcnt)) || ( counter > ((howManyWords/par)*parcnt)) )
		{
			fprintf( outfile, "\n\n" );
			parcnt++;
		}
	 	for( idx= 0; idx < ngramsBase->size; idx++ )
		{
			if( (strcmp( nGram->ngram, ngramsBase->ngramsBaseTab[idx].nGram->ngram )) == 0 )
			{
				/* znalazl taki n-gram w bazie ngramow */
        		isfound = 1;
				printf( "ngram:*%s*\n", nGram->ngram );
				ngramsBase->ngramsBaseTab[idx].nGram->cnt++;

				randidx = get_random_suffix( idx, ngramsBase, rand() );
				prob = calc_prob( ngramsBase, wTab, idx, randidx );
        		
				printf( "wylosowany indeks:%d z %zu mozliwych (sufiks:%s) z prawdopodobienstwem: %.3f\n", randidx, ngramsBase->ngramsBaseTab[idx].sufTab->size, wTab->wordsTab[ngramsBase->ngramsBaseTab[idx].sufTab->suffixes[randidx]]->word, prob );
        		
				fprintf( outfile, "%s ", wTab->wordsTab[ngramsBase->ngramsBaseTab[idx].sufTab->suffixes[randidx]]->word );
					
				if( randidx == -1 ) {
            	fprintf( stdout, "Nie znaleziono n-gramu. Koniec generowania tekstu.\n" );
            	return;
				}
					/* tworzenie nowego n-gramu */
					cnt = 0;
					sf = strchr( nGram->ngram, ' ' );
					while( (*sf++) != '\0' )
						cnt++;

					ssize = strlen( wTab->wordsTab[ngramsBase->ngramsBaseTab[idx].sufTab->suffixes[randidx]]->word );
					newnGram = ( ngram_t* )malloc( sizeof * newnGram );
					if( newnGram == NULL )
						fprintf( stderr, "\nBlad! Nie przyznano pamieci dla struktury nowego n-gramu.\n" );

					newnGram->ngram = ( char* )malloc( (ssize + cnt + 1) * sizeof (char ) );
					if( (newnGram->ngram) == NULL )
						fprintf( stderr, "\nBlad! Nie przydzielono pamieci dla nowego n-gramu.\n" );
					
					i = 0;
					for( pt= (strchr( nGram->ngram, ' ' )+1); *pt != '\0'; pt++ ) /*kopiuje reszte starego n-gramu do nowego n-gramu */
						newnGram->ngram[i++] = *pt;

					newnGram->ngram = strcat( newnGram->ngram, wTab->wordsTab[ngramsBase->ngramsBaseTab[idx].sufTab->suffixes[randidx]]->word );
					newnGram->ngram = strcat( newnGram->ngram, " " );
					printf( "stworzono nowy ngram:%s\n\n", newnGram->ngram );

					nGram->ngram = ( char* )realloc( nGram->ngram, (strlen( newnGram->ngram ) + 1) * sizeof (char) );
					if( (nGram->ngram) == NULL )
						fprintf( stderr, "\nBlad! Nie przydzielono miejsca dla nowego n-gramu w starym n-gramie.\n" );
					nGram->ngram = ( char* )memset( nGram->ngram, '\0', strlen( newnGram->ngram ) + 1 );

					nGram->ngram = strcpy( nGram->ngram, newnGram->ngram );
				
				sf = NULL;
				pt = NULL;
				counter++;
				break;
			}
		}
		if( isfound == 0 )
		{
		nGram = make_ngram2( wTab, randngram, rank );
		printf( "--\n" );
		printf( "nowy ngram:%s\n\n", nGram->ngram );
			fprintf( outfile, "%s", nGram->ngram );
			counter += rank;
		}
	 }
	 free(nGram);
	 free(newnGram);
	 free(sf);
	 free(pt);
	 printf( "\nKoniec tekstu.\n" );
    
	 fclose(outfile);
	 return;
}


void generate_text_from_base( wtab_t* wTab, nbtab_t* ngramsBase, int howManyWords, int rank, int seed, char* outFileName )
{
    ngram_t* nGram;
    ngram_t* newnGram;
	 char* sf, *pt = NULL;
    int randidx, counter, i, cnt = 0, isfound = 0, randngram, fcheck = 0;
	 size_t ssize, idx;
	 
	 FILE* outfile = fopen( outFileName, "w" );

		srand(seed);
	 /*randngram = (int)( rand()/(RAND_MAX + 1.0) * (ngramsBase->size-rank-1) );*/
	 randngram = ( rand() % (ngramsBase->size-rank) );
    printf( "randngram:%d\n", randngram );
	 
	nGram = ngramsBase->ngramsBaseTab[randngram].nGram;
    
	 printf( "START-->%s\n", nGram->ngram );
	 if( (fcheck = fputs( nGram->ngram, outfile )) == EOF )
	 	fprintf( stderr, "\nBlad! Nieudany zapis tekstu wyjsciowego do pliku.\n" );
	
    for( counter= rank; counter < howManyWords; )
    {
	 	isfound = 0;
	 	for( idx= 0; idx < ngramsBase->size; idx++ )
		{
			if( (strcmp( nGram->ngram, ngramsBase->ngramsBaseTab[idx].nGram->ngram )) == 0 )
			{
				/* znalazl taki n-gram w bazie ngramow */
        		isfound = 1;
				printf( "**ngram:*%s*\n", nGram->ngram );
				randidx = get_random_suffix( idx, ngramsBase, rand() );
				printf( "co jest w wTabSuf:%zu\n", wTab->size );
        		printf( "wylosowany indeks:%d z %zu mozliwych(sufiks:%s)\n", randidx, ngramsBase->ngramsBaseTab[idx].sufTab->size, wTab->wordsTab[ngramsBase->ngramsBaseTab[idx].sufTab->suffixes[randidx]]->word );
        		
				fcheck = 0;
				if( (fcheck = fputs( wTab->wordsTab[ngramsBase->ngramsBaseTab[idx].sufTab->suffixes[randidx]]->word, outfile )) == EOF )
					fprintf( stderr, "\nBlad! Nieudany zapis sufiksu do pliku.\n" );
				putc ( ' ', outfile );
					
				/*	fputs( wTab->wordsTab[ngramsBase->ngramsBaseTab[idx].sufTab->suffixes[randidx]]->word, outfile );
					putc( ' ', outfile );*/

				
				if( randidx == -1 )
				{
            	fprintf( stdout, "Nie znaleziono n-gramu. Koniec generowania tekstu.\n" );
            	return;
				}

					/* tworzenie nowego n-gramu */
					cnt = 0;
            	/*printf( "%s\n", wTab->wordsTab[ngramsBase->ngramsBaseTab[idx].sufTab->suffixes[randidx]]->word );
        			*/
					sf = strchr( nGram->ngram, ' ' );
					while( (*sf++) != '\0' )
						cnt++;

					ssize = strlen( wTab->wordsTab[ngramsBase->ngramsBaseTab[idx].sufTab->suffixes[randidx]]->word );
					
					newnGram = ( ngram_t* )malloc( sizeof * newnGram );
					if( newnGram == NULL )
						fprintf( stderr, "\nBlad! Nie przyznano pamieci dla struktury nowego n-gramu.\n" );

					newnGram->ngram = ( char* )malloc( (ssize + cnt + 1) * sizeof (char ) );
					if( (newnGram->ngram) == NULL )
						fprintf( stderr, "\nBlad! Nie przydzielono pamieci dla nowego n-gramu.\n" );
					
					i = 0;
					for( pt= (strchr( nGram->ngram, ' ' )+1); *pt != '\0'; pt++ ) /*kopiuje reszte starego n-gramu do nowego n-gramu */
						newnGram->ngram[i++] = *pt;
					printf( "co zostalo ze starego ngramu:%s\n", newnGram->ngram );

					newnGram->ngram = strcat( newnGram->ngram, wTab->wordsTab[ngramsBase->ngramsBaseTab[idx].sufTab->suffixes[randidx]]->word );
					newnGram->ngram = strcat( newnGram->ngram, " " );
					printf( "stworzono nowy ngram newnGram:%s\n", newnGram->ngram );

					nGram->ngram = ( char* )realloc( nGram->ngram, (strlen( newnGram->ngram ) + 1) * sizeof (char) );
					if( (nGram->ngram) == NULL )
						fprintf( stderr, "\nBlad! Nie przydzielono miejsca dla nowego n-gramu w starym n-gramie.\n" );
					nGram->ngram = ( char* )memset( nGram->ngram, '\0', strlen( newnGram->ngram ) + 1 );
					

					nGram->ngram = strcpy( nGram->ngram, newnGram->ngram );
					printf( "**nowy ngram:*%s*\n\n", nGram->ngram );
				
				sf = NULL;
				pt = NULL;
				counter++;
				break;
			}
		}
		if( isfound == 0 )
			nGram= ngramsBase->ngramsBaseTab[randngram].nGram;
		
		fcheck = 0;
		if( (fcheck = fputs( nGram->ngram, outfile )) == EOF )
			fprintf( stderr, "\nBlad! Nieudany zapis tekstu wyjsciowego do pliku.\n" );

    }
	 free(nGram);
	 free(newnGram);
	 free(sf);
	 free(pt);
	 printf( "\nKoniec tekstu.\n" );
    
	 fclose(outfile);
	 return;
}
