#ifndef _STATISTICS_SS_H_
#define	_STATISTICS_SS_H_

#include "file_parser.h"
#include "ngrams_base_creator2.h"
#include <stdio.h>

double calc_prob( ngram_t* );
double calc_pmi( ngram_t* );
int most_freq_ngram( nbtab_t* ); /*zwraca indeks w bazie ngramow najczesciej wystepujacego ngramu */


#endif

