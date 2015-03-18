#ifndef _WORD_LIST_H_
#define	_WORD_LIST_H_

struct ngram {
    char** ngram;
    int how_many;
    char** suffixes;
    double* prob_for_suf;
    struct ngram* next;
} ngram_t;

ngram_t* init_list();
ngram_t* add_ngram( ngram_t*, char** );
int get_ngram( ngram_t* );


#endif

