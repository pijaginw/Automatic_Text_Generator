#ifndef _GENERATOR_H_
#define	_GENERATOR_H_

#include "ngrams_base_creator2.h"
#include "statistics.h"
#include <stdio.h>
#include <string.h>

int get_random_suffix( int, nbtab_t*, int );
void generate_text( wtab_t*, nbtab_t*, int, int, int, int, char* );
void generate_text_from_base( wtab_t*, nbtab_t*, int, int, int, char* );
#endif

