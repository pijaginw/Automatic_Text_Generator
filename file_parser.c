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
    wtabs_t** newwordsTab = realloc( t->wordsTab, 2 * (t->capacity) * sizeof (wtabs_t**) );
    if( newwordsTab == NULL )
        fprintf( stderr, "\nBlad! Nie powiekszono tablicy słów!\n" );
    t->capacity *= 2;
    t->wordsTab = newwordsTab;
    for( i= tmp; i < t->capacity; i++ )
        t->wordsTab[i] = init_word_tab();
	 return t;
}

/*wtab_t* resize( wtab_t* t )
{
	int i;
	size_t tmp = t->capacity;
	t->wordsTab = ( wtabs_t** )realloc( t->wordsTab, 2 * t->capacity * sizeof (wtab_t*) );
	if( (t->wordsTab) == NULL )
		fprintf( stderr, "\nBlad! Nie powiekszono tablicy slow.\n" );
	t->capacity *= 2;
	for( i= 0; i < t->capacity; i++ )
		t->wordsTab[i] = init_word_tab();
	return t;
}*/

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
	 nw->word = ( char* )memset( nw->word, '\0', INIT_LENGTH_S );
    return nw;
}

wtabs_t* resizes( wtabs_t* ts )
{
    char* nw = realloc( ts->word, (ts->capacity+INIT_LENGTH_S+1) * sizeof * ts->word );
    if( nw == NULL )
        fprintf( stderr, "\nBlad! Brak pamieci dla tablicy słowa!\n" );
    ts->capacity += INIT_LENGTH_S;
	 ts->word = nw;
    return ts;
}

wtab_t* parse_file( char** filesTab, int filesCounter, wtab_t* wTab )
{
    char symb;
    int scount = 0; /*ilość symboli na stosie */
    int wordscount = 0; /*ilośc słów w tekstach bazowych */
    int i;
    
    FILE* infile = NULL;
	 list_t list = NULL;
    
    wTab = init_tab();
    
    for( i= 0; i < filesCounter; i++ )
    {
        infile = fopen( filesTab[i], "r" );
        printf("zaczynam czytac plik\n");
        
        if( infile == NULL )
            fprintf( stderr, "\nBlad! Nie mogę otworzyc pliku do czytania!\n" );
    
        while( (symb = fgetc(infile)) != EOF )
        {
				if( isgraph(symb) )
            {
                list = add_letter(list, symb);
                scount++;
            }
            if( isspace(symb) )
            {
                int i;
                if( (wTab->size) == (wTab->capacity) )
                    wTab = resize(wTab);
                for( i= 0; i < scount; i++ ) {
                    printf("(symbol %d)", i);

                    if( (wTab->wordsTab[wordscount]->size) == (wTab->wordsTab[wordscount]->capacity) )
                        wTab->wordsTab[wordscount] = resizes(wTab->wordsTab[wordscount]);
                    wTab->wordsTab[wordscount]->word[i] = list->letter;
						  printf( "-->%c   ", wTab->wordsTab[wordscount]->word[i] );
                    wTab->wordsTab[wordscount]->size++;
                    list = get_letter(list);
                }
                printf("\nkolejne (%d) slowo w tablicy:%s\n", wordscount+1, wTab->wordsTab[wordscount]->word );
                wordscount++;
                wTab->size++;
                scount = 0;
            }
        }
    }

	 fclose(infile);
    return wTab;
}
