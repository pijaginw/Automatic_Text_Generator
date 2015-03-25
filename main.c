/* 
 * File:   main.c
 * Author: Weronika
 *
 * Created on 12 marca 2015, 20:24
 */

#include "stack.h"
#include "file_parser.h"
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
    printf( "size wTab w main --- %d\n", wTab->size);
    
    /*test kolejki
    
    list_t list = NULL;
    list = add_letter(list, 'a');
    list = add_letter(list, 'b');
    list = add_letter(list, 'c');
    printf("cala lista:\n");
    print_list(list);
    printf("\n");
    list = get_letter(list);
    printf("bez 1:\n");
    print_list(list);
    printf("\n");
    list = get_letter(list);
    printf("bez 2:\n");
    print_list(list);
    printf("\n");
    list = get_letter(list);
    printf("bez 3:\n");
    print_list(list);
*/
    
    /*char** testowanie = make_ngram(2, wTab->wordsTab);*/
    
    
    return (EXIT_SUCCESS);
}
