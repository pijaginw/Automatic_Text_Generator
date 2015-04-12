/* 
 * File:   main.c
 * Author: Weronika
 *
 * Created on 12 marca 2015, 20:24
 */

#include "file_parser.h"
#include "ngrams_base_creator2.h"
#include "generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main( int argc, char** argv ) {

    int opt, idx, fcount = 0;
    int howManyFiles = 0;
    int rankNumber, wordsNumber, paragraphNumber;
    char* filesNames[1];
    char* basefileName = NULL;
    char* nextFile, *file;
    int index;
    
    wtab_t* wTab = init_tab();
    
    while(( opt = getopt( argc, argv, "t:m:n:l:p:" )) != -1) 
    {
        switch(opt)
        {
            case 't':
/*
                idx = optind-1;
                while(idx < argc)
                {
                    if(*argv[idx] != '-')
                    {
                        nextFile = strdup(argv[idx++]);
                        filesNames[fcount++] = nextFile;
                    }
                    else break;
                }
                break;
*/
                file = optarg;
                filesNames[0] = file;
                fcount = 1;
                break;
            case 'm':
                rankNumber = atoi(optarg);
                break;
            case 'n':
                wordsNumber = atoi(optarg);
                break;
            case 'l':
                paragraphNumber = atoi(optarg);
                break;
            case 'p':
                basefileName = optarg;
                break;
        }
    }
    printf("opcja rzedu ngramow: %d\nopcja liczby slow: %d\nile plikow: %d\n"
            "nazwa pliku: %s\nnazwa bazy: %s\n",rankNumber, wordsNumber, howManyFiles, file, basefileName);
    
    if( optind < argc )
        fprintf( stderr, "\nPodano zle argumenty!\n" );
    
/*
    if( file != NULL ) {
        FILE *inf = NULL;
    }
*/
    
    wTab = parse_file( filesNames, fcount, wTab );
    printf( "size wTab w main --- %zu\n", wTab->size);
	 printf( "co siedzi w wTab 1-->%s\n", wTab->wordsTab[0]->word );

    printf( "\n-----%c\n", wTab->wordsTab[0]->word[0]);

	int m;
	printf("-->size--%zu\n", wTab->size);

	ngram_t* ngram1 = make_ngram2(wTab, 0, 2);
	printf( "--ngram:%s\n", ngram1->ngram );

	ngram_t* ngram2 = make_ngram2(wTab, 1, 2);
	printf( "--ngram:%s\n", ngram2->ngram );

	ngram_t* ngram3 = make_ngram2(wTab, 2, 2);
	printf( "--ngram:%s\n", ngram3->ngram );

		  nbtab_t* ngramsBase = create_ngrams_base_tab( wTab, 2 );
		  print_ngramstab( ngramsBase, wTab );
		  generate_text( wTab, ngramsBase, 10, 2 );
/*
        index = get_random_suffix( ngramsList->nGram->ngram, ngramsList );
        if( index == -1 )
            printf( "nie znaleziono sufiksu\n" );
        else
            printf( "wylosowany indeks: %d\n", index );
        
*/
    return (EXIT_SUCCESS);
}
