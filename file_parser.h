#ifndef _FILE_PARSER_H_
#define	_FILE_PARSER_H_
#define INIT_LENGTH 10

#include <stdio.h>

typedef struct {
    char** wordsTab;
    size_t size;
    size_t capacity;
} wtab_t;

wtab_t* init_tab();
wtab_t* resize( wtab_t* );
char** parse_file( char**, int, wtab_t* ); /*czyta plik tekstowy i sklada slowa*/
int put_word_into_base( char*, char** ); /*umieszcza slowa w bazie*/

#endif

