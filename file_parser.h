#ifndef _FILE_PARSER_H_
#define	_FILE_PARSER_H_

#include <stdio.h>

char** parse_file( char* ); /*czyta plik tekstowy i sklada slowa*/
int put_word_into_base( char*, char** ); /*umieszcza slowa w bazie*/

#endif

