#ifndef _STATISTICS_SS_H_
#define	_STATISTICS_SS_H_

#include "file_parser.h"
#include "ngrams_base_creator2.h"
#include <stdio.h>

double calc_prob( nbtab_t*, wtab_t*, int, int );
double calc_pmi( ngram_t* );
void most_freq_ngrams( nbtab_t* ); /*zwraca indeks w bazie ngramow najczesciej wystepujacego ngramu */


#endif

