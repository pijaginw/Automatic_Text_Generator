#ifndef _NGRAMS_BASE_CREATOR_2_H
#define _NGRAMS_BASE_CREATOR_2_H

#include "file_parser.h"
#include <stdio.h>

#define INIT_S 50
#define INIT_SS 5

typedef struct {
	char* ngram;
	int cnt;
	size_t size;
	size_t capacity;
} ngram_t;

typedef struct {
	int* suffixes;
	size_t size;
	size_t capacity;
} suftab_t;

typedef struct {
	ngram_t* nGram;
	suftab_t* sufTab;
} ngrams_t;

typedef struct {
	ngrams_t* ngramsBaseTab;
	size_t size;
	size_t capacity;
} nbtab_t;

typedef struct {
	int* statsTab;
	size_t size;
	size_t capacity;
} sttab_t;

ngram_t* make_ngram2( wtab_t*, int, int );
suftab_t* make_suftab( void );
suftab_t* resize_suftab( suftab_t* );
sttab_t* make_sttab( void );
sttab_t* resize_sttab( sttab_t* );
nbtab_t* create_ngrams_base_tab( wtab_t*, char*, int );
nbtab_t* read_ngrams_from_base( wtab_t*, char*, int );
void print_ngramstab( nbtab_t* );

#endif
