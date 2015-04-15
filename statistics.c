#include "statistics.h"
#include <stdio.h>

double calc_prob( ngram_t* l ) {}
double calc_pmi( ngram_t* l ) {}

int most_freq_ngram( nbtab_t* ngramsBase )
{
	int maxsizeidx;
	size_t i;

	maxsizeidx = ngramsBase->ngramsBaseTab[0].sufTab->size;

	for( i= 1; i < ngramsBase->size; i++ )
		if( ngramsBase->ngramsBaseTab[i].sufTab->size > maxsizeidx )
			maxsizeidx = ngramsBase->ngramsBaseTab[i].sufTab->size;
		else
			return 0;

	return maxsizeidx;
}
