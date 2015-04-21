#include "statistics.h"
#include <stdio.h>

double calc_prob( nbtab_t* ngramsBase, wtab_t* wTab, int idx, int randidx ) 
{
	int i, counter = 0;
	double prob;

	for( i= 0; i < ngramsBase->ngramsBaseTab[idx].sufTab->size; i++ )
		if( strcmp(wTab->wordsTab[ngramsBase->ngramsBaseTab[idx].sufTab->suffixes[randidx]]->word, wTab->wordsTab[ngramsBase->ngramsBaseTab[idx].sufTab->suffixes[i]]->word) == 0 )
			counter++;

	prob = ( 1.0/(ngramsBase->ngramsBaseTab[idx].sufTab->size) )*(counter);
	return prob;
}

/*double calc_pmi( nbtab_t* ngramsBase, wtabt_t* wTab, int idx, int cnt ) 
{
	double pmi, wsum;
	char* ptr;
	char word[128];
	int i, k;

	while( *(ptr = ngramsBase->ngramsBaseTab[idx].nGram->ngram ) != ' ' )
		word[i++] = *(ptr++);

	for( k = 0; k < wTab->size; k++ )
		if( (strcmp( wTab->wordsTab[k]->word )) == 0 )
			wsum += 1/wTab->size; 

	pmi = log( (cnt/ngramsBase->size) / ()
}*/

void most_freq_ngrams( nbtab_t* ngramsBase )
{
	int max1, max2, max3, cnt1, cnt2, cnt3;
	size_t i;

	max1 = 0;
	for( i= 1; i < ngramsBase->size; i++ )
		if( ngramsBase->ngramsBaseTab[i].sufTab->size > ngramsBase->ngramsBaseTab[max1].sufTab->size ) {
			max1 = i;
		}
	
	max2 = 0;
	for( i= 1; i < ngramsBase->size; i++ ) {
		if( i == max1 )
			continue;
		if( ngramsBase->ngramsBaseTab[i].sufTab->size > ngramsBase->ngramsBaseTab[max2].sufTab->size )
			max2 = i;
	}
	
	max3 = 0;
	for( i= 1; i < ngramsBase->size; i++ ) {
		if( i == max1 )
			continue;
		if( i == max2 )
			continue;
		if( ngramsBase->ngramsBaseTab[i].sufTab->size > ngramsBase->ngramsBaseTab[max2].sufTab->size )
			max3 = i;
	}

	printf( "\n---Statystyka---\n" );
	printf( "\nNajczęściej występujący n-gram: %s (wystąpił %zu raz(y))\n", ngramsBase->ngramsBaseTab[max1].nGram->ngram, ngramsBase->ngramsBaseTab[max1].sufTab->size );
	printf( "Drugi najczęściej występujący n-gram: %s (wystąpił %zu raz(y))\n", ngramsBase->ngramsBaseTab[max2].nGram->ngram, ngramsBase->ngramsBaseTab[max2].sufTab->size );	
	printf( "Trzeci najczęściej występujący n-gram: %s (wystąpił %zu raz(y))\n\n", ngramsBase->ngramsBaseTab[max3].nGram->ngram, ngramsBase->ngramsBaseTab[max3].sufTab->size );
	
	cnt1 = 0;
	for( i= 1; i < ngramsBase->size; i++ )
		if( ngramsBase->ngramsBaseTab[i].nGram->cnt > ngramsBase->ngramsBaseTab[cnt1].nGram->cnt )
			cnt1 = i;
	printf( "Najczęściej wylosowany n-gram: %s (wylosowany %d raz(y))\n", ngramsBase->ngramsBaseTab[cnt1].nGram->ngram, ngramsBase->ngramsBaseTab[cnt1].nGram->cnt );

	cnt2 = 0;
	for( i= 1; i < ngramsBase->size; i++ ) {
		if( i == cnt1 )
			continue;
		else if( ngramsBase->ngramsBaseTab[i].nGram->cnt > ngramsBase->ngramsBaseTab[cnt2].nGram->cnt )
				cnt2 = i;
	}
	printf( "Drugi najczęściej wylosowany n-gram: %s (wylosowany %d raz(y))\n", ngramsBase->ngramsBaseTab[cnt2].nGram->ngram, ngramsBase->ngramsBaseTab[cnt2].nGram->cnt );
	
	cnt3 = 0;
	for( i= 1; i < ngramsBase->size; i++ ) {
		if( (i == cnt2) || (i == cnt1) )
			continue;
		if( ngramsBase->ngramsBaseTab[i].nGram->cnt > ngramsBase->ngramsBaseTab[cnt3].nGram->cnt )
			cnt3 = i;
	}
	printf( "Trzeci najczęściej wylosowany n-gram: %s (wylosowany %d raz(y))\n\n", ngramsBase->ngramsBaseTab[cnt3].nGram->ngram, ngramsBase->ngramsBaseTab[cnt3].nGram->cnt );
	return;

}
