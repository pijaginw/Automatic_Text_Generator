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
    int rankNumber, wordsNumber, paragraphNumber;
    char* filesNames[1];
    char* outputFileName = NULL, *indBaseFileName = NULL;
    char* nextFile, *file;
    int index, maxidx, m;
    
    wtab_t* wTab = init_tab();
    
    while(( opt = getopt( argc, argv, "t:m:n:l:p:b:" )) != -1) 
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
                outputFileName = optarg;
                break;
				case 'b':
					indBaseFileName = optarg;
					break;
       }
   }
   printf("opcja rzedu ngramow: %d\nopcja liczby slow: %d\nile plikow: %d\n"
            "nazwa pliku: %s\nnazwa bazy: %s\n",rankNumber, wordsNumber, howManyFiles, file, outputFileName);
    
   if( optind < argc )
       fprintf( stderr, "\nPodano zle argumenty!\n" );
    
   wTab = parse_file( filesNames, fcount, wTab );
	nbtab_t* ngramsBase = create_ngrams_base_tab( wTab, indBaseFileName, rankNumber );
	print_ngramstab( ngramsBase, wTab );
	generate_text( wTab, ngramsBase, wordsNumber, rankNumber, rand(), outputFileName );
	maxidx = most_freq_ngram( ngramsBase );

	for( m= 0; m < wTab->size; m++ )
		printf( "%s	", wTab->wordsTab[m]->word );
	printf( "\n\n" );
	printf( "stats: najczęściej występujący n-gram: \"%s\"\n\n", ngramsBase->ngramsBaseTab[maxidx].nGram->ngram );
    
	 return (EXIT_SUCCESS);
}
