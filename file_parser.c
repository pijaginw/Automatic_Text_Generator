#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

list_t const list;
char** base_text;

int parse_file( char *filename )
{
    char symb;
    int scount = 0;
    int wordscount = 0; /*ilośc słów w tekstach bazowych */
    FILE *infile = fopen( filename, "r" );
    
    while( (symb = fgetc(infile)) != EOF )
    {
        if( (symb >= 'A' && symb <= 'Z') || (symb >= 'a' && symb <= 'z') )
        {
            add_letter(list, symb);
            scount++;
        }
        if( isspace(symb) )
        {
            int i;
            char c;
            for( i=0; i < scount; i++ ) {
                c = get_letter(list);
                base_text[wordscount][i] = c;
            }
            wordscount++;
        }
            
        
    }
}

int put_word_into_base( char* word, char** tab) 
{

}
