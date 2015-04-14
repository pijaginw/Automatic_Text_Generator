#include "ngrams_base_creator2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ngram_t* make_ngram2( wtab_t* wTab, int idx, int rank )
{
	size_t i, tmp = 0, k;
	ngram_t* newnGram;

	newnGram = ( ngram_t* )malloc( sizeof * newnGram );
	if( newnGram == NULL )
		fprintf( stderr, "\bBlad! Nie przydzielono pamieci dla struktury ngramu.\n" );

	newnGram->ngram = ( char* )malloc( INIT_SS * sizeof (char) );
	if( (newnGram->ngram) == NULL )
		fprintf( stderr, "\nBlad! Brak pamieci dla ngramu.\n" );

	newnGram->size = 0;
	newnGram->capacity = INIT_SS;
	newnGram->ngram = ( char* )memset( newnGram->ngram, '\0', INIT_SS );

	for( i= 0; i < rank; i++ )
	{
		if( (newnGram->size + strlen(wTab->wordsTab[idx]->word)+1) > newnGram->capacity )
		{
			char* nw = ( char* )realloc( newnGram->ngram, (newnGram->capacity + INIT_SS) * sizeof (char) );
			if( nw == NULL )
				fprintf( stderr, "\nBlad! Nie powiekszono ngramu.\n" );

			newnGram->ngram = nw;
			tmp = newnGram->capacity;
			newnGram->capacity += INIT_SS;
			for( k = tmp; k < newnGram->capacity; k++ )
				newnGram->ngram[k] = '\0';

			/*free(nw);*/
		}
		newnGram->ngram = strcat( newnGram->ngram, wTab->wordsTab[idx++]->word );
		newnGram->ngram = strcat( newnGram->ngram, " " );

		newnGram->size += strlen( newnGram->ngram );
	}
	return newnGram;
}

suftab_t* make_suftab()
{
	suftab_t* nt;

	nt = ( suftab_t* )malloc( sizeof * nt );
	if( nt == NULL )
		fprintf( stderr, "\nBlad! Nie przyznano pamieci dla struktury tablicy sufiksow.\n" );
	
	nt->suffixes = ( int* )malloc( INIT_SS * sizeof (int) );
	if( (nt->suffixes) == NULL )
		fprintf( stderr, "\nBlad! Nie przydzielono pamieci dla tablicy sufiksow.\n" );

	nt->size = 0;
	nt->capacity = INIT_SS;

	/*free(nt);*/
	return nt;
}

suftab_t* resize_suftab( suftab_t* s )
{
	int* ns = ( int* )realloc( s->suffixes, 2 * (s->capacity) * sizeof (int) );
	if( ns == NULL )
		fprintf( stderr, "\nBlad! Nie powiekszono tablicy sufiksow.\n" );

	s->capacity *= 2;
	s->suffixes = ns;

	/*free(ns);*/
	return s;
}

nbtab_t* create_ngrams_base_tab( wtab_t* wTab, int rank )
{
	size_t idx, idxtab;
	int istrue = 0;
	nbtab_t* ngramsBase;
	ngram_t* newnGram;
	ngrams_t* newEl;

	ngramsBase = ( nbtab_t* )malloc( sizeof * ngramsBase );
	if( ngramsBase == NULL )
		fprintf( stderr, "\nBlad! Nie przydzielono pamieci dla struktury tablicy ngramow.\n" );

	ngramsBase->ngramsBaseTab = ( ngrams_t* )malloc( INIT_S * sizeof * ngramsBase->ngramsBaseTab );
	if( (ngramsBase->ngramsBaseTab) == NULL )
		fprintf( stderr, "\nBlad! Nie przydzielono pamieci dla tablicy struktur ngramow.\n" );

	ngramsBase->size = 0;
	ngramsBase->capacity = INIT_S;

	for( idx= 0; idx < wTab->size-rank; idx++ ) /*iteruje po tablicy slow*/
	{
		istrue = 0;
		newnGram = make_ngram2( wTab, idx, rank );
		printf( "opracowywany ngram:%s\n", newnGram->ngram );
		printf( "rozmiar tablicy ngramow:%zu\n", ngramsBase->size );
		printf( "pojemnosc tablicy ngramow:%zu\n\n", ngramsBase->capacity );
		
		for( idxtab= 0; idxtab < ngramsBase->size; idxtab++ ) /* iteruje po tablicy n-gramow */
		{
			if( (strcmp( newnGram->ngram, (ngramsBase->ngramsBaseTab[idxtab]).nGram->ngram )) == 0 )
			{	
				istrue = 1;
				printf( "znalazlem taki ngram!!\n" );
				if( ((ngramsBase->ngramsBaseTab[idxtab]).sufTab->size) == ((ngramsBase->ngramsBaseTab[idxtab]).sufTab->capacity ) )
					(ngramsBase->ngramsBaseTab[idxtab]).sufTab = resize_suftab( (ngramsBase->ngramsBaseTab[idxtab]).sufTab );
				(ngramsBase->ngramsBaseTab[idxtab]).sufTab->suffixes[ngramsBase->ngramsBaseTab[idxtab].sufTab->size++] = idx+rank;
				break;
			}
		}
		/* nie znalazl takiego ngramu, trzeba stworzyc nowy element bazy */
		if( istrue == 0 )
		{
			newEl = ( ngrams_t* )malloc( sizeof * newEl );
			if( newEl == NULL )
				fprintf( stderr, "\nBlad! Nie przydzielono pamieci dla nowego elementu tablicy.\n" );

			newEl->nGram = newnGram;
			newEl->sufTab = make_suftab();
			newEl->sufTab->suffixes[newEl->sufTab->size++] = idx+rank;

			if( (ngramsBase->size) == (ngramsBase->capacity) ) {
				ngramsBase->ngramsBaseTab = ( ngrams_t* )realloc( ngramsBase->ngramsBaseTab, 2 * (ngramsBase->capacity) * sizeof * ngramsBase->ngramsBaseTab );
				if( (ngramsBase->ngramsBaseTab) == NULL )
					fprintf( stderr, "\nBlad! Nie powiekszono tablicy n-gramow.\n" );
				
				ngramsBase->capacity *= 2;
			}
			ngramsBase->ngramsBaseTab[ngramsBase->size] = *newEl;
			/*printf( "nowy ngram:%s\n", ngramsBase->ngramsBaseTab[idx].nGram->ngram );*/
			ngramsBase->size++;
		}
	}
	return ngramsBase;
}

void print_ngramstab( nbtab_t* ngramsBase, wtab_t* wTab )
{
	size_t i;
	printf( "\n\ntest tablicy ngramow:\n" );
	for( i= 0; i < ngramsBase->size; i++ ) {
		printf( "oto ngram %zu:%s\n", i, ngramsBase->ngramsBaseTab[i].nGram->ngram );
	}
	return;
}

