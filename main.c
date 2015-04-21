/* 
 * File:   main.c
 * Author: Weronika
 *
 * Created on 12 marca 2015, 20:24
 */

#include "file_parser.h"
#include "generator.h"
#include "statistics.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main( int argc, char** argv ) {

    int opt, idx, fcount = 0;
    int howManyFiles = 0;
    int rankNumber, wordsNumber, paragNumber;
    char* filesNames[1];
    char* outputFileName = NULL, *indBaseFileName = NULL;
    char* nextFile, *file;
    int index, maxidx, m;
   
	char** filesNames2;
    wtab_t* wTab = init_tab();
    wtab_t* wTabSuf = init_tab();

    while(( opt = getopt( argc, argv, "t:m:n:l:p:b:" )) != -1) 
    {
        switch(opt)
        {
            case 't':
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
                paragNumber = atoi(optarg);
                break;
            case 'p':
                outputFileName = optarg;
                break;
				case 'b':
					indBaseFileName = optarg;
					break;
       }
   }
    
   if( optind < argc )
       fprintf( stderr, "\nPodano zle argumenty!\n" );

	srand(time(NULL));
   wTab = parse_file( filesNames, fcount, wTab );
	nbtab_t* ngramsBase = create_ngrams_base_tab( wTab, indBaseFileName, rankNumber );
	print_ngramstab( ngramsBase );
	generate_text( wTab, ngramsBase, wordsNumber, paragNumber, rankNumber, rand(), outputFileName );
	/*tryb czytania z bazy
	nbtab_t* ngramsBase = read_ngrams_from_base( wTabSuf, indBaseFileName, rankNumber );
	printf( "\n\nile jest sufiksow:%zu\n\n", wTabSuf->size );
	generate_text_from_base( wTabSuf, ngramsBase, wordsNumber, rankNumber, rand(), outputFileName );*/

	most_freq_ngrams( ngramsBase );
	printf( "Liczba słów w tekstach bazowych: %zu\n", wTab->size );
	printf( "Liczba wszystkich n-gramów: %zu\n", ngramsBase->size );
	printf( "Rząd n-gramów: %d\n", rankNumber );
	printf( "Liczba wygenerowanych slow: %d\n", wordsNumber );
	printf( "Liczba akapitów: %d\n\n", paragNumber );
	printf( "-----------------\n\n" );

	 free_wtab( wTab );
	 return (EXIT_SUCCESS);
}
