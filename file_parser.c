#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** parse_file( char** filesTab, int filesCounter, char** wordsTab )
{
    char symb;
    int scount = 0;
    int wordscount = 0; /*ilośc słów w tekstach bazowych */
    int i;
    
    list_t list = init_list();
    FILE* infile = NULL;
    
    for( i= 0; i < filesCounter; i++ )
    {
        FILE *infile = fopen( filesTab[i], "r" );
    
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
                for( i= 0; i < scount; i++ ) {
                    c = get_letter(list);
                    wordsTab[wordscount][i] = c;
                }
                wordscount++;
            }
        }
    }
}

int put_word_into_base( char* word, char** base ) 
{

}
