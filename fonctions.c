#include <stdlib.h> 
#include <string.h>
#include <stdio.h> 
#include <dirent.h> 
#include "fonctions.h"
#ifndef WIN32

    #include <sys/types.h>

#endif

int findDefine (char* chaine, int here);

/* permet de trouver le nom d'une fonction grace aux caractere valide d'un nom de fonction*/
int allowed (char crt){
    if ((crt >= 'a' &&  crt <= 'z') || (crt >= '0' && crt <= '9') || crt == '_' || (crt >= 'A' && crt <= 'Z'))
        return 1;  
    
    else
        return 0;
}

/* permet d'ignorer les elements du C ressemblant à une fonction tel que if, for ... */
int notLoop (char *fonctionName){
    int taille = strlen(fonctionName);
    if(strncmp (fonctionName, "if", taille) == 0|| strncmp (fonctionName,"for", taille) == 0|| strncmp (fonctionName, "while", taille) == 0 || strncmp (fonctionName,"else if", taille) == 0|| strncmp(fonctionName,"return", taille) == 0){    
        return 0;
    }
    return 1;
}

/* permet d'ignorer les fonctions entre guillemet*/
int ignorerGuillemet (char *lesCrt, int here){
    int i = here+1;
    while (lesCrt[i] != '"')
        i++;
    return i+1;
}

/* permet d'ignorer les fonctions dans un commentaire*/
int ignorerCommentaire (char *lesCrt, int here){
    int i = here+2;
    if (lesCrt[i-1] == '/'){
        while (lesCrt[i] != '\n'){
            i++;
        }
    }
    if (lesCrt[i-1] == '*'){
        while(lesCrt[i] != '*' && lesCrt[i] != '/')
            i++;
    }
    return i;
}

/* remplit ma 1er liste*/
char* trouvFonction (char *lesCrt, int *here, int op){
    int start, end, len;
    unsigned int i;
    i = *here;
    int isFonction = 0;
    while (lesCrt[i] != '('){
        if (lesCrt[i] == '"')
           i = ignorerGuillemet(lesCrt,i);
        if (lesCrt[i] == '/' && lesCrt[i+1] == '*')
            i = ignorerCommentaire(lesCrt,i);
        if (lesCrt[i] == '/' && lesCrt[i+1] == '/')
            i = ignorerCommentaire(lesCrt,i);
        if (i == strlen(lesCrt)){
            *here = i;
            return NULL;
        }
        i++;
    }
    //printf("%c\n", lesCrt[i]);
    //printf ("%c\n",lesCrt[findDefine(lesCrt, i)]);
    isFonction = findDefine(lesCrt, i);
    *here = i+1;
    i--;
    while (allowed(lesCrt[i]) != 1 && lesCrt[i] == ' ')
        i--;
    end = i;
    while (allowed(lesCrt[i]) == 1)
        i--;
    start = i;
    len = end - start ;
    char *fonctionName = calloc(len, (sizeof(char)));
    for (int j = 0; j < len; j++){
        fonctionName[j] = lesCrt[start+j+1];
    }
    if (notLoop (fonctionName) == 1 && len > 0){
        if (isFonction == 1){
            if (op == 0)
                return strcat (fonctionName,":");
            if (op == 1)
                return fonctionName;
        }
        return fonctionName;
    }
    return NULL;
}



char** fonctionsListe (char* chaine, int len, int* taille, int op){
    int nbFct = 0;
    char* nomFct;
    char** lesFct = malloc (100*sizeof(*lesFct));
    int j = 0;
    while (j < len){
        nomFct = trouvFonction(chaine, &j, op);
        
        if (nomFct != NULL){
            //realloc(lesFct, nbFct*sizeof(*lesFct));
            lesFct[nbFct] = malloc (strlen(nomFct)*sizeof(*lesFct[nbFct]));
            strcpy (lesFct[nbFct], nomFct);
            nbFct++;
        }  
    }
    if ((realloc (lesFct, nbFct*sizeof(*lesFct))) == NULL)
        printf("error1\n");
    *taille = nbFct;
    return lesFct;
}

/* permet d'ignorer les fonctions deja existante pour ma 2eme liste*/
char* notExiste (char** fonctions, char* chaine, int taille){
    int size = strlen(chaine);

    for (int i = 0; i < taille; ++i) {
        if (strncmp(fonctions[i], chaine, size) == 0)
            return NULL;
    }

    return chaine;
}

/* recupere ma 2eme liste */
char** onlyOne (char** all, int* t){
    int taille = *t;
    int oneTaille = 1;
    char* testExist;

    char** one = malloc (taille*sizeof(*one));
    for (int i = 0; i < taille; ++i)
        one[i]= malloc (0*sizeof(*one[i]));

    for (int i = 0 ; i < taille ; i++){
        testExist = notExiste(one, all[i], taille);
        if (testExist){
            one[oneTaille-1] = testExist;
            oneTaille++;
        }
    }
    if ((realloc(one, oneTaille*sizeof(*one))) == NULL)
        printf("error2\n");
    *t = oneTaille-1;   
    return one;
}


/* permet de reconnaire une definition de fonction */
int findDefine (char* chaine, int here){
    int i = here;
    int parenthese = 1;
    //printf("find : %c\n", chaine[here]);
    while (parenthese != 0){
        i++;
        if (chaine[i] == '(')
            parenthese++;
        if (chaine[i] == ')')
            parenthese--;
    } 
    i++;
    while(chaine[i] == ' ')
        i++;
    if(chaine[i] == '{')
        return 1;
    return 0;

}


void affiche (char** fonctions, int taille){
    for (int i = 0; i < taille; ++i)
        printf("%d. %s\n", i+1, fonctions[i]);
}

