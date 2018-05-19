#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "get_programme.h"
#include "mat.h"
#include "fonctions.h"
#include "brin.h"

void options (){
    printf("====================================================================================\n");
    printf("ENTREZ UN NUMERO D'OPTION: \n\n");
    printf("-(1) Pour afficher les noeuds.\n");
    printf("-(2) Pour afficher la matric.\n");
    printf("-(3) Pour afficher le tableau de brin (brin/noeud/suivant).\n");
    printf("-(4) Pour afficher les elements connexe d'un noeud.\n");
    printf("-(5) Pour afficher les cycles d'un noeud.\n");
    printf("-(6) Pour comparer les algorithmes de recherche d'elements connexe (mat et brin).\n");
    printf("-(7) Pour comparer les algorithmes de recherche de cycle (mat et brin).\n");
    printf("-(8) Pour quitter.\n");
}

int main(int argc, char *argv[]) {
    int option;
    int noeud;
	int nbCrt = 0;
    char* programme = openFile(argc,argv, &nbCrt);
    mat_t m;
	int tailleAll = 0;
    char** all = fonctionsListe(programme,nbCrt, &tailleAll, 0);  
    clock_t a, b, end;

    while(1){
        option = 0;
        do{
            options();
            scanf("%d", &option);
        } while(option < 1 || option > 8);

        printf("====================================================================================\n");
        int tailleOne = tailleAll;   
        char** one = onlyOne(fonctionsListe(programme,nbCrt, &tailleAll, 3), &tailleOne);

        if (option == 1)
            affiche (one, tailleOne);

        m = fillMat(all, one, tailleAll, tailleOne);

        if (option == 2)
            afficheMat(m);

        m = numArrete(fillMat(all, one, tailleAll, tailleOne), tailleOne);

        tabBrins  tabB = tableauBrin (numArrete( m, tailleOne), tailleOne);

        if (option == 3)
            afficheColonne (tabB, nombreArrete(m, tailleOne));

        if (option == 4){
            printf("Choisisé un noeud :\n");
            scanf("%d", &noeud);

            printf("Avec Mat\n");
            afficheConnexion (trouverConnexion (m, noeud-1, tailleOne), noeud-1);
            printf("Avec Brin\n");
            afficheConnexion_brin (trouverConnexionBrin (tabB, noeud, nombreArrete (m, tailleOne)), noeud);
        }

        if (option == 5){
            printf("Choisisé un noeud :\n");
            scanf("%d", &noeud);

            printf("Avec Mat\n");
            trouverCycle (m, noeud-1, tailleOne);
            printf("Avec Brin\n");
            trouverCycle_brin (tabB, noeud, tailleOne);
        }

        if (option == 6){
            printf("Choisisé un noeud :\n");
            scanf("%d", &noeud);

            printf("Avec Mat :\n");
            a = clock();
            afficheConnexion (trouverConnexion (m, noeud-1, tailleOne), noeud-1);
            b = clock();    
            end = (double)(b - a);
            printf ("temps : %f \n", (double)end);
            printf("\n");
            printf("Avec Brin :\n");
            a = clock();
            afficheConnexion_brin (trouverConnexionBrin (tabB, noeud, nombreArrete (m, tailleOne)), noeud);
            b = clock();    
            end = (double)(b - a);
            printf ("temps : %f \n", (double)end);

        }

        if (option == 7){
            printf("Choisisé un noeud :\n");
            scanf("%d", &noeud);

            printf("Avec Mat :\n");
            a = clock();
            trouverCycle (m, noeud-1, tailleOne);
            b = clock();    
            end = (double)(b - a);
            printf ("temps : %f \n", (double)end);
            printf("\n");
            printf("Avec Brin :\n");
            a = clock();
            trouverCycle_brin (tabB, noeud, tailleOne);
            b = clock();    
            end = (double)(b - a);
            printf ("temps : %f \n", (double)end);

        }



        if (option == 8)
            break;

    }

    return 0;
}         

