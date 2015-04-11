#ifndef _GENERATOR_H_
#define	_GENERATOR_H_

#include "ngrams_base_creator.h"
#include <stdio.h>
#include <string.h>

int get_random_suffix( char*, ngrams_t* );
void generate_text( wtab_t*, ngrams_t*, int, int );
#endif

