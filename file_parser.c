#include "stack.h"
#include "file_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

wtab_t* init_tab() 
{
    int i;
    wtab_t* nw = malloc( sizeof * nw );
    if( nw == NULL )
        fprintf( stderr, "\nBlad! Brak pamieci dla struktury tablicy slów!\n" );
    nw->wordsTab = malloc( INIT_LENGTH * sizeof * *(nw->wordsTab) );
    if( (nw->wordsTab) == NULL )
        fprintf( stderr, "\nBlad! Brak pamieci dla tablicy słowa!\n" );
    for( i= 0; i < INIT_LENGTH; i++)
        nw->wordsTab[i] = init_word_tab();
    nw->size = 0;
    nw->capacity = INIT_LENGTH;
    return nw;
}

wtab_t* resize( wtab_t* t )
{
    int i;
	 size_t tmp = t->capacity;
    wtabs_t** newwordsTab = realloc( t->wordsTab, 2 * t->capacity * sizeof **newwordsTab );
    if( newwordsTab == NULL )
        fprintf( stderr, "\nBlad! Nie powiekszono tablicy słów!\n" );
    t->capacity *= 2;
    t->wordsTab = newwordsTab;
	 /*newwordsTab = t->wordsTab;*/
    for( i= tmp; i < t->capacity; i++ )
    /*for( i= (t->capacity)/2; i < t->capacity; i++ )*/
        t->wordsTab[i] = init_word_tab();
    return t;
}

wtabs_t* init_word_tab()
{
    wtabs_t* nw = malloc( sizeof * nw );
    if( nw == NULL )
        fprintf( stderr, "\nBlad! Brak pamieci dla struktury tablicy slowa!\n" );
    nw->word = malloc( INIT_LENGTH_S * sizeof (char) );
    if( (nw->word) == NULL )
        fprintf( stderr, "\nBlad! Brak pamieci dla tablicy słowa!\n" );
    nw->size = 0;
    nw->capacity = INIT_LENGTH_S;
    return nw;
}

wtabs_t* resizes( wtabs_t* ts )
{
    wtabs_t* nw = realloc( ts->word, 2 * ts->capacity * sizeof (char) );
    if( nw == NULL )
        fprintf( stderr, "\nBlad! Brak pamieci dla tablicy słowa!\n" );
    nw->capacity *= 2;
	 nw = ts;
    return nw;
}

wtab_t* parse_file( char** filesTab, int filesCounter, wtab_t* wTab )
{
    char symb;
    int scount = 0; /*ilość symboli na stosie */
    int wordscount = 0; /*ilośc słów w tekstach bazowych */
    int i;
    
    list_t list = NULL;
    FILE* infile = NULL;
    
    wTab = init_tab();
    
    for( i= 0; i < filesCounter; i++ )
    {
        infile = fopen( filesTab[i], "r" );
        
        printf("zaczynam czytac plik\n");
        
        if( infile == NULL )
            fprintf( stderr, "\nBlad! Nie mogę otworzyc pliku do czytania!\n" );
    
        while( (symb = fgetc(infile)) != EOF )
        {
            printf("pobieram symbol\n");
            if( (symb >= 'A' && symb <= 'Z') || (symb >= 'a' && symb <= 'z') || symb == '.' || symb == ',' )
            {
                printf("symbol jest literą\n");
                list = add_letter(list, symb);
                scount++;
            }
            if( isspace(symb) )
            {
                int i;
                /*wTab = init_tab();*/
                if( (wTab->size) == (wTab->capacity) )
                    wTab = resize(wTab);
                for( i= 0; i < scount; i++ ) {
                    printf("wkładam symbol %d do tablicy slowa", i);

                    if( (wTab->wordsTab[wordscount]->size) == (wTab->wordsTab[wordscount]->capacity) )
                        wTab->wordsTab[wordscount] = resizes(wTab->wordsTab[wordscount]);
                    wTab->wordsTab[wordscount]->word[i] = list->letter;
						  printf( "-->%c\n", wTab->wordsTab[wordscount]->word[i] );
                    wTab->wordsTab[wordscount]->size++;
                    list = get_letter(list);
                }
                printf("po zapakowaniu slowa %d\n", wordscount+1);
                wordscount++;
                printf( "----%d----\n", wordscount );
                wTab->size++;
                /*wTab->wordsTab[wordscount]->size = 0;*/
                scount = 0;
            }
        }
    }
    return wTab;
}
