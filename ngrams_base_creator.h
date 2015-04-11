#ifndef _NGRAMS_BASE_CREATOR_H_
#define	_NGRAMS_BASE_CREATOR_H_

#include "file_parser.h"
#include <stdio.h>

#define INIT_SIZE 10
#define INIT_SF_SIZE 3

/*Tworzenie ngramow oraz ich listy*/
/* Oraz bazy n-gramow zapisywanej do pliku dodatkowego !!*/

/*tutaj przechowywany jest jeden sufiks */
typedef struct suffix {
    char* suffix;
    double prob; /*prawdopodobieństwo wystapienia sufiksu */
    size_t size;
    size_t capacity;
} suf_t; 

/*dynamiczna tablica sufiksów*/
typedef struct suftab {
    suf_t* stab;
    size_t size;
    size_t capacity;
} suftab_t;

/*tutaj przechowywany jest jeden ngram */
typedef struct ngram {
    char* ngram;
    int ngramCount; /*liczba wystąpień ngramu */
    size_t size;
    size_t capacity;
} ngram_t;

typedef struct ngrams {
    ngram_t* nGram; /*dyn tab dla jednego n-gramu */
    suftab_t* sufTab;
    struct ngrams* next;
} ngrams_t;

ngrams_t* ngramsList;
/*chyba tak byłoby lepiej
 struct elemngram {
    char* ngram;
    int ngramCount;
    struct suffix* sufTab;
    struct ngrams* next;
 };*/

suf_t init_suf();
char* resize_suf( suf_t* );
suftab_t* init_suf_tab();
suftab_t* resize_suf_tab( suftab_t* );
suftab_t* add_suffix( suftab_t* );
ngram_t* make_ngram( int, int, wtab_t* ); /*tworzy i zwraca ngram o podanym rzedzie */
ngrams_t* create_ngrams_base( wtab_t*, int ); /*tworzy i zwraca pełną listę ngramow */
void print_ngramsList( ngrams_t* );
void delete_list( ngrams_t* );
char* get_ngram( ngrams_t* );

#endif

