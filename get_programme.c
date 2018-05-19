#include <stdlib.h> 
#include <string.h>
#include <stdio.h> 
#include <dirent.h> 
#include <limits.h>
#include "get_programme.h"
#ifndef WIN32

    #include <sys/types.h>

#endif

char* openFile (int argc, char* argv[], int* nb){
    char* chaine = malloc(UINT_MAX* sizeof(*chaine));
    FILE* fichier = NULL;
    int caractereActuel;
    int i = 0;
    if (argc != 2)
        printf("error3\n");
    
    fichier = fopen(argv[1], "r");
    if (fichier != NULL){
        do{
                caractereActuel = fgetc(fichier);
                chaine[i] = caractereActuel;
                i++;
        } 
        while (caractereActuel != EOF);
            fclose(fichier);
    }   
    if (realloc(chaine, (i) * sizeof(*chaine)) == NULL)
        printf("error4\n");
    *nb = i;
    return chaine;
}