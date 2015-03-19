#ifndef _STATISTICS_H_
#define	_STATISTICS_H_

#include "file_parser.h"
#include "ngrams_list.h"
#include <stdio.h>

double calc_prob( ngram_t* );
double calc_pmi( ngram_t* );

#endif

