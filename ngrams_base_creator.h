#ifndef _NGRAMS_BASE_CREATOR_H_
#define	_NGRAMS_BASE_CREATOR_H_

#include "file_parser.h"
#include <stdio.h>

/*Tworzenie ngramow oraz ich listy*/

typedef struct ngram {
    char* ngram;
    int how_many; /*ilosc wystapień danego n-gramu */
    char** suffixes;
    double* prob_for_suf; /*prawdopodobieństwo wystapienia sufiksu */
    struct ngram* next;
} ngram_t;

char* make_ngram( int, char** ); /*tworzy i zwraca ngram o podanym rzedzie */
ngram_t* make_base();
ngram_t* create_ngrams_base( char**, ngram_t*, int, int ); /*tworzy i zwraca listę ngramow */
int get_ngram( ngram_t* );

#endif

