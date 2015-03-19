/* 
 * File:   main.c
 * Author: Weronika
 *
 * Created on 12 marca 2015, 20:24
 */

#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main( int argc, char** argv ) {

    int opt;
    int idx, fcount = 0;
    int howManyFiles = 0;
    int rankNumber;
    int wordsNumber;
    int paragraphNumber;
    char **fileNames, *baseName = NULL;
    char *nextFile, *file;
    
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
                        fileNames[fcount++] = nextFile;
                    }
                    else break;
                }
                break;
*/
                file = optarg;
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
                baseName = optarg;
                break;
        }
    }
    printf("opcja rzedu ngramow: %d\nopcja liczby slow: %d\nile plikow: %d\n"
            "nazwa pliku: %s\nnazwa bazy: %s\n",rankNumber, wordsNumber, howManyFiles, file, baseName);
    
    if( optind < argc )
        fprintf( stderr, "\nPodano zle argumenty!\n" );
    
    if( file != NULL ) {
        FILE *inf = NULL;
    }
    
    /*test kolejki*/
    
    list_t list = init_list();
    add_letter(list, 'a');
    add_letter(list, 'b');
    add_letter(list, 'c');
    print_list(list);
    printf("\n");
    char c1 = get_letter(list);
    print_list(list);
    printf("\n");
    char c2 = get_letter(list);
    print_list(list);
    printf("\n");
    char c3 = get_letter(list);
    
    return (EXIT_SUCCESS);
}
