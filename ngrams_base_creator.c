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
	news = ( char* )memset( news, '\0', INIT_SF_SIZE );
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

suf_t init_suf()
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
    return *ns;
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

ngrams_t* create_ngrams_base( wtab_t* wTab, int rank ) 
{
    int i, idx = 0;
    int istrue;
    ngram_t* newnGram;
    ngrams_t* ngramsList; /*glowa listy */
    ngrams_t* ntmp = NULL, *tmp = NULL;
    ngrams_t* newEl;
    
    ngramsList = ( ngrams_t* )malloc( sizeof *ngramsList );
	 if( ngramsList == NULL )
	 	fprintf( stderr, "\nBlad! Nie przydzielono pamieci dla glowy listy.\n" );
	
	/*tmp = ( ngrams_t* )malloc( sizeof * tmp );
	if( tmp == NULL )
	 	fprintf( stderr, "\nBlad! Nie przydzielono pamieci dla tmp.\n" );
	ntmp = ( ngrams_t* )malloc( sizeof * ntmp );
	if( ntmp == NULL )
	 	fprintf( stderr, "\nBlad! Nie przydzielono pamieci dla glowy ntmp.\n" );*/

	 ngramsList->next = NULL;
    
    for( idx= 0; idx < wTab->size-rank; idx++ ) 
    {
        istrue = 0;
        newnGram = make_ngram( rank, idx, wTab );
        printf(" nowy ngram:%s\n", newnGram->ngram );
        
        tmp = ngramsList;
        while( tmp != NULL )
        {
            if( (strcmp( newnGram->ngram, tmp->nGram->ngram )) == 0 )
            {
                istrue = 1;
					 printf("znalazlem taki ngram w liscie\n");
                if( (tmp->sufTab->size) == (tmp->sufTab->capacity) )
                    tmp->sufTab = resize_suf_tab( tmp->sufTab );
						  printf( "hmmmmm a co tutaj siedzi?? **%s**\n", tmp->sufTab->stab[0].suffix );
                if( ( strlen( wTab->wordsTab[idx+rank]->word )) > tmp->sufTab->stab[tmp->sufTab->size].size )
					 {
                  tmp->sufTab->stab[tmp->sufTab->size].suffix = resize_suf( tmp->sufTab->stab );
                	tmp->sufTab->stab[tmp->sufTab->size].capacity *= 2;
					 }
                tmp->sufTab->stab[++tmp->sufTab->size].suffix = wTab->wordsTab[idx+rank]->word;
					 tmp->sufTab->stab[tmp->sufTab->size].size += strlen( wTab->wordsTab[idx]->word );
					 printf( "sufiks:%s\n", tmp->sufTab->stab[--tmp->sufTab->size].suffix );
                tmp->sufTab->size++;
					 tmp->nGram->ngramCount++;
					 break;
            }
            tmp = tmp->next;
        }
        
        if( istrue == 0 )
        {
		  		ntmp = ( ngrams_t* )malloc( sizeof * ntmp );
            ntmp = ngramsList;
            while( ntmp != NULL )
                ntmp = ntmp->next;
        
            newEl = ( ngrams_t* )malloc( sizeof * newEl );
            if( newEl == NULL)
                fprintf( stderr, "\nBlad! Brak pamieci dla nowego elementu listy n-gramow!\n" );
        
				/*ntmp->next = newEl;*/
            
            newEl->nGram = newnGram;
            newEl->nGram->ngramCount++;
            newEl->sufTab = init_suf_tab();
				printf( "hmm co siedzi w suftab?? **%s**\n", newEl->sufTab->stab[0].suffix );
            newEl->sufTab->stab[newEl->sufTab->size++].suffix = wTab->wordsTab[idx+rank]->word;
				printf( "sufiks:%s\n", newEl->sufTab->stab[--newEl->sufTab->size].suffix );
				newEl->sufTab->size++;
           
			  /*	ntmp->next = ( ngrams_t* )malloc( sizeof * (ntmp->next) );
				if( (ntmp->next) == NULL )
					fprintf( stderr, "\nBlad! Nie przydzielono pamieci dla nastepnego elementu.\n" );*/
				ntmp->next = newEl;
            newEl->next = NULL;
        }
    }
	 free(tmp);
	 free(ntmp);
	 free(newnGram);
    return ngramsList;
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
