#include "ngrams_base_creator2.h"
#include "file_parser.h"
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

	newnGram->ngram = ( char* )malloc( (INIT_SS+1) * sizeof (char) );
	if( (newnGram->ngram) == NULL )
		fprintf( stderr, "\nBlad! Brak pamieci dla ngramu.\n" );

	newnGram->cnt = 0;
	newnGram->size = 0;
	newnGram->capacity = INIT_SS;
	newnGram->ngram = ( char* )memset( newnGram->ngram, '\0', newnGram->capacity );

	for( i= 0; i < rank; i++ )
	{
		while( (newnGram->size + strlen(wTab->wordsTab[idx]->word) +1 ) > newnGram->capacity )
		{
			char* nw = realloc( newnGram->ngram, (newnGram->capacity + INIT_SS) * sizeof (char) );
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
	suftab_t* nt = ( suftab_t* )malloc( sizeof * nt );
	if( nt == NULL )
		fprintf( stderr, "\nBlad! Nie przyznano pamieci dla struktury tablicy sufiksow.\n" );
	
	nt->suffixes = ( int* )malloc( INIT_SS * sizeof (int) );
	if( (nt->suffixes) == NULL )
		fprintf( stderr, "\nBlad! Nie przydzielono pamieci dla tablicy sufiksow.\n" );

	nt->size = 0;
	nt->capacity = INIT_SS;

	return nt;
}

suftab_t* resize_suftab( suftab_t* s )
{
	int* ns = ( int* )realloc( s->suffixes, (INIT_SS + s->capacity) * sizeof (int) );
	if( ns == NULL )
		fprintf( stderr, "\nBlad! Nie powiekszono tablicy sufiksow.\n" );

	s->capacity += INIT_SS;
	s->suffixes = ns;
	return s;
}

sttab_t* make_sttab()
{
	sttab_t* ns = ( sttab_t* )malloc( sizeof * ns );
	if( ns == NULL )
		fprintf( stderr, "\nBlad! Nie przydzielono pamieci.\n" );
	
	ns->statsTab = ( int* )malloc( INIT_SS * sizeof (int) );
	if( (ns->statsTab) == NULL )
		fprintf( stderr, "\nBlad! Nie przyznano pamieci.\n" );

	ns->size = 0;
	ns->capacity = INIT_SS;

	return ns;
}

sttab_t* resize_sttab( sttab_t* st )
{
	int* ns = ( int* )realloc( st->statsTab, (INIT_SS + st->capacity) * sizeof (int) );
	if( ns == NULL )
		fprintf( stderr, "\nBlad! Nie przydzielono pamieci.\n" );

	st->capacity += INIT_SS;
	st->statsTab = ns;
	return st;
}

nbtab_t* create_ngrams_base_tab( wtab_t* wTab, char* indBaseFileName, int rank )
{
	size_t idx, idxtab, i, j;
	int istrue = 0, fcheck = 0, c;
	char c1 = '#', c2 = '/', c3 = '\n';
	nbtab_t* ngramsBase;
	ngram_t* newnGram;
	ngrams_t* newEl;

	FILE* outfile = fopen( indBaseFileName, "w" );

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
		
		for( idxtab= 0; idxtab < ngramsBase->size; idxtab++ ) /* iteruje po tablicy n-gramow */
		{
			if( (strcmp( newnGram->ngram, (ngramsBase->ngramsBaseTab[idxtab]).nGram->ngram )) == 0 )
			{	
				istrue = 1;
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
				ngramsBase->ngramsBaseTab = ( ngrams_t* )realloc( ngramsBase->ngramsBaseTab, (INIT_S + ngramsBase->capacity) * sizeof * ngramsBase->ngramsBaseTab );
				if( (ngramsBase->ngramsBaseTab) == NULL )
					fprintf( stderr, "\nBlad! Nie powiekszono tablicy n-gramow.\n" );
				
				ngramsBase->capacity += INIT_S;
			}
			ngramsBase->ngramsBaseTab[ngramsBase->size] = *newEl;
			ngramsBase->size++;
		}
	}
	for( i= 0; i < ngramsBase->size; i++ )
	{
		fcheck = 0;
		if( (fcheck = fputs( ngramsBase->ngramsBaseTab[i].nGram->ngram, outfile )) == EOF )
			fprintf( stderr, "\nBlad! Nie zapisano tekstu do bazy posredniej.\n" );

		c = fputc( c1, outfile );
		c = fputc( c3, outfile );
		for( j= 0; j < ngramsBase->ngramsBaseTab[i].sufTab->size; j++ )
		{
			fcheck = 0;
			if( (fcheck = fputs( wTab->wordsTab[ngramsBase->ngramsBaseTab[i].sufTab->suffixes[j]]->word, outfile )) == EOF )
				fprintf( stderr, "\nBlad! Nie zapisano sufiksu do bazy posredniej.\n" );
			
			c = fputc( c2, outfile );
			if( j == (ngramsBase->ngramsBaseTab[i].sufTab->size-1) )
			c = fputc( c2, outfile );
			c = fputc( c3, outfile );
		}
	}

	fclose(outfile);
	return ngramsBase;
}

void print_ngramstab( nbtab_t* ngramsBase )
{
	size_t i;
	printf( "\n\ntest tablicy ngramow:\n" );
	for( i= 0; i < ngramsBase->size; i++ ) {
		printf( "--->ngram %zu:%s\n", i, ngramsBase->ngramsBaseTab[i].nGram->ngram );
	}
	return;
}

nbtab_t* read_ngrams_from_base( wtab_t* wTabSuf, char* indBaseFileName, int rank )
{
	char *newLine, *suf, *newnGram, *tmp, *symb, ch;
	size_t cnt;
	int index = 0, idx = 0, isLast;
	nbtab_t* ngramsBase = NULL;
	ngrams_t* newEl = NULL;
	FILE* infile = fopen( indBaseFileName, "r" );

	wTabSuf = init_tab();
	symb = ( char* )malloc( sizeof (char ) );

	ngramsBase = ( nbtab_t* )malloc( sizeof * ngramsBase );
	if( ngramsBase == NULL )
		fprintf( stderr, "\nBlad! Nie przydzielono pamieci dla struktury tablicy ngramow.\n" );

	ngramsBase->ngramsBaseTab = ( ngrams_t* )malloc( INIT_S * sizeof * ngramsBase->ngramsBaseTab );
	if( (ngramsBase->ngramsBaseTab) == NULL )
		fprintf( stderr, "\nBlad! Nie przydzielono pamieci dla tablicy struktur ngramow.\n" );

	ngramsBase->size = 0;
	ngramsBase->capacity = INIT_S;

	newLine = ( char* )malloc( 1024 * sizeof (char) );
	newLine = ( char* )memset( newLine, '\0', 1024 );

	while( (newLine = fgets( newLine, 1024, infile )) != NULL )
	{	
		isLast = 0;
		if( (symb = strrchr( newLine, '#' )) != NULL ) /*wczytuje n-gram*/
		{
			cnt = 0;
			tmp = newLine;
			while( (ch = (*tmp++)) != '#' )
				cnt++;

			newEl = ( ngrams_t* )malloc( sizeof * newEl );
			if( newEl == NULL )
				fprintf( stderr, "\nBlad! Nie przydzielono pamieci dla nowego elementu tablicy.\n" );

			newEl->nGram = ( ngram_t* )malloc( sizeof * newnGram );
			if( (newEl->nGram) == NULL )
				fprintf( stderr, "\nBlad! Nie przydzielono pamieci dla struktury ngramu.\n" );

			newEl->nGram->ngram = ( char* )malloc( (cnt+1) * sizeof (char) );
			if( (newEl->nGram->ngram) == NULL )
				fprintf( stderr, "\nBlad! Brak pamieci dla ngramu.\n" );

			newEl->nGram->size = cnt;
			newEl->nGram->capacity = INIT_SS; /*troche zle, ale nie ma to znaczenia */
			newEl->nGram->ngram = ( char* )memset( newEl->nGram->ngram, '\0', cnt+1 );
			newEl->nGram->ngram = strncpy( newEl->nGram->ngram, newLine, cnt );

			newEl->sufTab = make_suftab();

			if( (ngramsBase->size) == (ngramsBase->capacity) ) {
				ngramsBase->ngramsBaseTab = ( ngrams_t* )realloc( ngramsBase->ngramsBaseTab, (INIT_S + ngramsBase->capacity) * sizeof * ngramsBase->ngramsBaseTab );
				if( (ngramsBase->ngramsBaseTab) == NULL )
					fprintf( stderr, "\nBlad! Nie powiekszono tablicy n-gramow.\n" );
				
				ngramsBase->capacity += INIT_S;
			}
			ngramsBase->ngramsBaseTab[ngramsBase->size] = *newEl;
			printf( "Wczytano %zu ngram:%s\n", ngramsBase->size, newEl->nGram->ngram );

		}
		else if( (symb = strrchr( newLine, '/' )) != NULL )
		{
			if( (*(--symb)) == '/' ) 
				isLast = 1;

			cnt = 0;
			tmp = newLine;
			suf = ( char* )malloc( 128 * sizeof (char ) );
			suf = ( char* )memset( suf, '\0', 128 );
			while( ( ch = (*tmp++)) != '/' )
			{
				suf[cnt++] = ch;
			}

			if( (wTabSuf->size) == (wTabSuf->capacity) )
				wTabSuf = resize( wTabSuf );

			if( cnt != 0 )
			while( cnt-1 > (wTabSuf->wordsTab[wTabSuf->size]->capacity) )
				wTabSuf->wordsTab[wTabSuf->size] = resizes( wTabSuf->wordsTab[wTabSuf->size] );
			wTabSuf->wordsTab[wTabSuf->size]->word = strcpy( wTabSuf->wordsTab[wTabSuf->size]->word, suf );
			printf( "Wczytano sufiks:%s, jest ich juz %zu\n", wTabSuf->wordsTab[wTabSuf->size]->word, wTabSuf->size );

			if( (ngramsBase->ngramsBaseTab[ngramsBase->size].sufTab->size) == (ngramsBase->ngramsBaseTab[ngramsBase->size].sufTab->capacity) )
				ngramsBase->ngramsBaseTab[ngramsBase->size].sufTab = resize_suftab( ngramsBase->ngramsBaseTab[ngramsBase->size].sufTab );
			ngramsBase->ngramsBaseTab[ngramsBase->size].sufTab->suffixes[ngramsBase->ngramsBaseTab[ngramsBase->size].sufTab->size++] = wTabSuf->size;
			wTabSuf->size++;
			printf( "Jest %zu sufiksow.\n", ngramsBase->ngramsBaseTab[ngramsBase->size].sufTab->size );

			if( isLast == 1 )
				ngramsBase->size++;
		}
	}
	fclose(infile);
	return ngramsBase;
}
