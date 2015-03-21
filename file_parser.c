#include "stack.h"
#include "file_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

wtab_t* init_tab() 
{
    wtab_t* nw = NULL;
    nw->wordsTab = malloc( INIT_LENGTH * sizeof * (nw->wordsTab) );
    if( (nw->wordsTab) == NULL )
        fprintf( stderr, "\nBlad! Brak pamieci dla struktury tablicy slów!\n" );
    nw->size = 0;
    nw->capacity = INIT_LENGTH;
    return nw;
}

wtab_t* resize( wtab_t* t ) 
{
    t->wordsTab = ( char** )realloc( t->wordsTab, 2 * sizeof (t->wordsTab) );
    if( (t->wordsTab) == NULL )
        fprintf( stderr, "\nBlad! Brak pamieci dla bazy słów!\n" );
    t->capacity = 2 * (t->capacity);
    return t;
}

char** parse_file( char** filesTab, int filesCounter, wtab_t* wTab )
{
    char symb;
    int scount = 0; /*ilość symboli na stosie */
    int wordscount = 0; /*ilośc słów w tekstach bazowych */
    int i;
    
    list_t list = NULL;
    FILE* infile = NULL;
    
    //wTab = init_tab();
    
    for( i= 0; i < filesCounter; i++ )
    {
        infile = fopen( filesTab[i], "r" );
        if( infile == NULL )
            fprintf( stderr, "\nBlad! Nie mogę otworzyc pliku do czytania!\n" );
    
        while( (symb = fgetc(infile)) != EOF )
        {
            printf("zaczynam czytac plik\n");
            if( (symb >= 'A' && symb <= 'Z') || (symb >= 'a' && symb <= 'z') || symb == '.' || symb == ',' )
            {
                printf("jestem w petli if\n");
                list = add_letter(list, symb);
                scount++;
            }
            if( isspace(symb) )
            {
                int i;
                for( i= 0; i < scount; i++ ) {
                    if( (wTab->size) == (wTab->capacity) )
                        wTab = resize(wTab);
                    list = get_letter(list);
                    (wTab->wordsTab)[wordscount][i] = list->letter;
                }
                printf("jestem w innym ifie\n");
                wordscount++;
                wTab->size++;
            }
        }
    }
    return wTab->wordsTab;
}

int put_word_into_base( char* word, char** base ) 
{

}
