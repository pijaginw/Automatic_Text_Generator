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

wtabs_t* init_word_tab()
{
    wtabs_t* nw = malloc( sizeof * nw );
    if( nw == NULL )
        fprintf( stderr, "\nBlad! Brak pamieci dla struktury tablicy slowa!\n" );
    nw->word = malloc( (INIT_LENGTH_S+1) * sizeof (char) );
    if( (nw->word) == NULL )
        fprintf( stderr, "\nBlad! Brak pamieci dla tablicy słowa!\n" );
    nw->size = 0;
    nw->capacity = INIT_LENGTH_S+1;
	 nw->word = ( char* )memset( nw->word, '\0', nw->capacity );
    return nw;
}

wtabs_t* resizes( wtabs_t* ts )
{
    char* nw = realloc( ts->word, (ts->capacity+INIT_LENGTH_S) * sizeof * ts->word );
    size_t tmp = ts->capacity;
	 int i;
	 if( nw == NULL )
        fprintf( stderr, "\nBlad! Brak pamieci dla tablicy słowa!\n" );
    ts->capacity += INIT_LENGTH_S;
	 ts->word = nw;
	 for( i = tmp; i < ts->capacity; i++ )
	 	ts->word[i] = '\0';
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

                    if( (wTab->wordsTab[wordscount]->size) == (wTab->wordsTab[wordscount]->capacity) )
                        wTab->wordsTab[wordscount] = resizes(wTab->wordsTab[wordscount]);
                    wTab->wordsTab[wordscount]->word[i] = list->letter;
                    wTab->wordsTab[wordscount]->size++;
                    list = get_letter(list);
                }
                wordscount++;
                wTab->size++;
                scount = 0;
            }
        }
    }

	 fclose(infile);
    return wTab;
}

void free_wtab( wtab_t* wTab )
{
	int i;
	for( i= 0; i < wTab->size; i++ )
		free(wTab->wordsTab[i]->word);
	free(wTab->wordsTab);
	free(wTab);
	return;
}
