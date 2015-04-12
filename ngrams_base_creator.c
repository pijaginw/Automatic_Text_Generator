#include "ngrams_base_creator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* !!
 * dodać generowanie pliku bazowego z n-gramami 
 * !!! */

char* init_suffix()
{
	char* news = ( char* )malloc( INIT_SF_SIZE * sizeof (char) );
	if( news == NULL )
		fprintf( stderr, "\nBlad! Brak pamieci dla sufiksu w init_suffix()!\n" );
/*	news = ( char* )memset( news, '\0', INIT_SF_SIZE );*/
	return news;
}

suftab_t* init_suf_tab() 
{
    int i;
    suftab_t* nsf = malloc( sizeof * nsf );
    if( nsf == NULL )
        fprintf( stderr, "\nBlad! Brak pamieci dla struktury tablicy sufiksów!\n" );
    nsf->stab = ( suf_t* )malloc( sizeof * (nsf->stab) );
    if( (nsf->stab) == NULL )
        fprintf( stderr, "\nBlad! Brak pamieci dla tablicy sufiksów!\n" );
    for( i= 0; i < INIT_SF_SIZE; i++)
	 {
        nsf->stab[i].suffix = init_suffix();
			nsf->stab[i].size = 0;
			nsf->stab[i].capacity = INIT_SF_SIZE;
    }
	 nsf->size = 0;
    nsf->capacity = INIT_SIZE;
    return nsf;
}

suftab_t* resize_suf_tab( suftab_t* sufTab )
{
	size_t i;
	size_t tmp = sufTab->capacity;
    suftab_t* nst = ( suftab_t* )realloc( sufTab, 2 * (sufTab->capacity) * sizeof (char) );
    if( nst == NULL )
        fprintf( stderr, "\nBlad! Brak pamieci dla struktury tablicy sufiksow!\n" );
    nst->capacity *= 2;
    sufTab = nst;
	 suf_t* nstab = ( suf_t* )malloc( sizeof * nstab );
	 if( nstab == NULL )
	 	fprintf( stderr, "\nBlad! Nie przydzielono pamieci dla nowego stab!\n" );
	sufTab->stab = nstab;
	for( i= tmp; i < sufTab->capacity; i++ )
	{
		nst->stab[i].suffix = init_suffix();
		nst->stab[i].size = 0;
		nst->stab[i].capacity = INIT_SIZE;
	}
	 printf("powiekszylem chyba tablice sufiksow\n");
    return nst;
}

char* resize_suf( suf_t* s )
{
	size_t i;
	size_t tmpc;
    suf_t* ns = ( suf_t* )malloc( sizeof * ns );
	 if( ns == NULL )
	 	fprintf( stderr, "\nBlad! Brak pamieci dla struktury sufiksu!\n" );

	tmpc = s->capacity;
    ns->suffix = ( char* )realloc( s, 2 * (s->capacity) * sizeof (char) );
    if( (ns->suffix) == NULL )
        fprintf( stderr, "\nBlad! Brak pamieci dla sufiksu w resize\n" );
    ns->capacity *= 2;
    s = ns;
	 for( i = tmpc; i < s->capacity; i++ )
	 	s->suffix[i] = '\0';

    return s->suffix;
}

nbtab_t* init_ngrams_base_tab()
{
	int i;
	nbtab_t* newBase = ( nbtab_t* )malloc( sizeof * newBase );
	if( newBase == NULL )
		fprintf( stderr, "\nBlad! Nie przydzielono pamieci dla struktury tablicy n-gramow.\n" );
	/*for( i= 0; i < INIT_SIZE; i++ )
	{*/
		ngrams_t* newBaseTab = ( ngrams_t* )malloc( INIT_SIZE * sizeof (ngrams_t) );
		if( newBaseTab == NULL )
			fprintf( stderr, "\nBlad! Nie przydzielono pamieci dla tablicy ngramow.\n" );
	newBase->ngramsBaseTab = newBaseTab;
	for( i= 0; i < INIT_SIZE; i++ )
	{
		/*newBase->ngramsBaseTab = newBaseTab;*/
		newBase->ngramsBaseTab[i].nGram->ngram = ( char* )malloc( INIT_SIZE * sizeof (char ) );
		newBase->ngramsBaseTab[i].nGram->size = 0;
		newBase->ngramsBaseTab[i].nGram->capacity = INIT_SIZE;
	/*	newBase->ngramsBaseTab[i].sufTab->stab[i].suffix = init_suffix();*/
		newBase->ngramsBaseTab[i].sufTab->size = 0;
		newBase->ngramsBaseTab[i].sufTab->capacity = INIT_SIZE;
		newBase->ngramsBaseTab[i].nGram->ngram = memset( newBase->ngramsBaseTab[i].nGram->ngram, '\0', INIT_SIZE );
		/*newBase->ngramsBaseTab[i].sufTab->stab[i].suffix = memset( newBase->ngramsBaseTab[i].sufTab->stab[i].suffix, '\0', INIT_SIZE );*/
	}
	return newBase;
}

ngram_t* make_ngram( int rank, int idx, wtab_t* wTab ) 
{
    int i;
    size_t capacity = INIT_SIZE;
    
    ngram_t* newNgram = ( ngram_t* )malloc( sizeof * newNgram );
    if( newNgram == NULL)
        fprintf( stderr, "\nBlad! Brak pamieci dla tablicy n-gramu\n" );
    
    newNgram->ngram = ( char* )malloc( capacity * sizeof (char) );
    if( (newNgram->ngram) == NULL)
        fprintf( stderr, "\nBlad! Brak pamieci dla n-gramu\n" );
    
    newNgram->capacity = capacity;
    newNgram->size = 0;
    newNgram->ngramCount = 0;
   
	newNgram->ngram = ( char* )memset( newNgram->ngram, '\0', newNgram->capacity );

    for( i= 0; i < rank; i++ ) {
        if( (newNgram->size + wTab->wordsTab[idx]->size) > newNgram->capacity )
        {
		  		char* nw = ( char* )realloc( newNgram->ngram, 2 * newNgram->capacity * sizeof (char) );
            /*newNgram->ngram = realloc( newNgram->ngram, 2 * newNgram->capacity);*/
				if( nw == NULL )
					fprintf( stderr, "\nBlad! Brak pamieci dla sufiksu\n" );
            newNgram->capacity *= 2;
				strcpy( nw, newNgram->ngram );
				newNgram->ngram = nw;
				newNgram->ngram = ( char* )memset( newNgram->ngram, '\0', newNgram->capacity );
        }
        newNgram->ngram = strcat( newNgram->ngram, wTab->wordsTab[idx++]->word );
        newNgram->ngram = strcat( newNgram->ngram, " " );

        newNgram->size = strlen( newNgram->ngram );
    }
		printf( "size of newNgram->ngram: %zu\n", newNgram->size );
    return newNgram;
}

nbtab_t* create_ngrams_base( wtab_t* wTab, int rank ) 
{
    int i, idx = 0;
    int istrue;
	 nbtab_t* ngramsBase;
    ngram_t* newnGram;
    ngrams_t* newEl;
   
	ngramsBase = init_ngrams_base_tab();

    for( idx= 0; idx < wTab->size-rank; idx++ ) 
    {
        istrue = 0;
        newnGram = make_ngram( rank, idx, wTab );
        printf(" nowy ngram:%s\n", newnGram->ngram );
        
        for( i = 0; i < ngramsBase->size; i++ )
        {
            if( (strcmp( ngramsBase->ngramsBaseTab[i].nGram->ngram, ngramsBase->ngramsBaseTab[idx].nGram->ngram )) == 0 )
            {
                istrue = 1;
					 printf("znalazlem taki ngram w tablicy\n");
                if( (ngramsBase->ngramsBaseTab[i].sufTab->size) == (ngramsBase->ngramsBaseTab[i].sufTab->capacity) )
                    ngramsBase->ngramsBaseTab[i].sufTab = resize_suf_tab( ngramsBase->ngramsBaseTab[i].sufTab );
						  printf( "hmmmmm a co tutaj siedzi?? **%s**\n", ngramsBase->ngramsBaseTab[i].sufTab->stab[0].suffix );
                if( ( strlen( wTab->wordsTab[idx+rank]->word )) > ngramsBase->ngramsBaseTab[i].sufTab->stab[ngramsBase->ngramsBaseTab[i].sufTab->size].size )
					 {
                  ngramsBase->ngramsBaseTab[i].sufTab->stab[ngramsBase->ngramsBaseTab[i].sufTab->size].suffix = resize_suf( ngramsBase->ngramsBaseTab[i].sufTab->stab );
                	ngramsBase->ngramsBaseTab[i].sufTab->stab[ngramsBase->ngramsBaseTab[i].sufTab->size].capacity *= 2;
					 }
                ngramsBase->ngramsBaseTab[i].sufTab->stab[++ngramsBase->ngramsBaseTab[i].sufTab->size].suffix = wTab->wordsTab[idx+rank]->word;
					 ngramsBase->ngramsBaseTab[i].sufTab->stab[ngramsBase->ngramsBaseTab[i].sufTab->size].size += strlen( wTab->wordsTab[idx]->word );
					 printf( "sufiks:%s\n", ngramsBase->ngramsBaseTab[i].sufTab->stab[--ngramsBase->ngramsBaseTab[i].sufTab->size].suffix );
                ngramsBase->ngramsBaseTab[i].sufTab->size++;
					 ngramsBase->ngramsBaseTab[i].nGram->ngramCount++;
					 break;
            }
        }
        
        if( istrue == 0 )
        {
		  		newEl = ( ngrams_t* )malloc( sizeof * newEl );
					fprintf( stderr, "\nBlad! Nie przydzielono pamieci dla nowego elementu tablicy ngramow.\n" );
            newEl->nGram = newnGram;
            newEl->nGram->ngramCount++;
            newEl->sufTab = init_suf_tab();
				printf( "hmm co siedzi w suftab?? **%s**\n", newEl->sufTab->stab[0].suffix );
            newEl->sufTab->stab[newEl->sufTab->size++].suffix = wTab->wordsTab[idx+rank]->word;
				printf( "sufiks:%s\n", newEl->sufTab->stab[--newEl->sufTab->size].suffix );
				newEl->sufTab->size++;
				ngramsBase->ngramsBaseTab[i] = *newEl;
				ngramsBase->size++;
        }
    }
	 free(newnGram);
    return ngramsBase;
}

void print_ngramsList( ngrams_t* ngramsList )
{
    int i;
	 ngrams_t* p = ngramsList;
    printf( "\n\ntest tworzenia listy ngramow:\n" );
    while( p != NULL )
    {
        printf( "ngram:%s\n", p->nGram->ngram );
        printf( "sufiks:%s\n", ngramsList->sufTab->stab[0].suffix );
        p = p->next;
    }
	 free(p);
	 return;
}
void print_ngramsbase( nbtab_t* ngramsBase )
{
	int i;
	printf( "testowanie tablicy ngramow:\n" );
	for( i= 0; i < ngramsBase->size; i++ ) {
		printf( "ngram:%s\n", ngramsBase->ngramsBaseTab[i].nGram->ngram );
		printf( "suffix[0]:%s\n", ngramsBase->ngramsBaseTab[i].sufTab->stab[0].suffix );
	}
	return;
}
void delete_list( ngrams_t* ngramsList )
{
	while( ngramsList->next->next != NULL ){
		ngramsList = ngramsList->next;
		free(ngramsList->next);
		ngramsList->next = NULL;
	}
}

char* get_ngram( ngrams_t* list ) 
{
    char* ngram;
    
    if( list != NULL )
        ngram = list->nGram->ngram;
    
    return ngram;
}
