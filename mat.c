#include <stdlib.h> 
#include <string.h>
#include <stdio.h> 
#include "mat.h"
#include <limits.h>
//#include "analyse.h"

/* initialise ma matrice à 0 partout */
mat_t initMat (int taille){
	mat_t m;
	m.n = taille;
	m.m = malloc(taille*sizeof(*m.m));

	for (int i = 0; i < taille; i++)
    	m.m[i] = malloc(taille*sizeof(**m.m));

	for (int i = 0; i < taille; ++i){
		for (int j = 0; j < taille; ++j)
			m.m[i][j] = 0;
	}
	return m;
}


int trouvInterval(char** one, char* chaine, int taille){
	for (int i = 0; i < taille; ++i){
		if (strcmp(chaine, one[i]) == 0){
			return i;
		}
	}
	return -1;
}

/* permet de reconnaire si une fonction est un definition de fonction (si ':' se trouve la fin de la chaine */
int is2Points (char* chaine){
	if (chaine[strlen(chaine)-1] == ':'){
		return 1;
	}
	return 0;

}


/* Remplit ma matrice en se servant des 2 listes remplis au préalable */
mat_t fillMat (char** all, char** one, int tailleAll, int tailleOne){
	mat_t m = initMat (tailleOne);
	int j;

	for (int i = 0; i < tailleOne; ++i) {
		j = 0;
		for (j = 0; j < tailleAll; j++){
			if ((strncmp(one[i], all[j], strlen(one[i])) == 0) && all[j][strlen(one[i])] == ':'){
				break;
			}
			
		}
		j++;
			while (j < tailleAll){
				if (is2Points(all[j]) == 0){
					if (trouvInterval(one, all[j], tailleOne) >= 0)
						m.m[i][trouvInterval(one, all[j], tailleOne)] = 1;
				}
				else if (is2Points(all[j]) == 1) 
					break;
				j++;
			}
	}

	return m;
}

/* affiche une matrice */
void afficheMat (mat_t m){
	for (int i = 0; i < m.n ; ++i){
		for (int j = 0; j < m.n; ++j){	
			if (m.m[i][j] > 9)
				printf("%d ", m.m[i][j]);
			else
				printf("%d ", m.m[i][j]);
		}
		printf("\n");
	}
}

/* Pour la liste de noued déja visité verifie si le noeud est deja visité */
int repetition (int* liste, int e, int taille){
	for (int i = 0; i < taille; ++i){
		if (liste[i] == e)
			return 1;
	}
	return 0;
}

/* parcourt en largeur permettant de trouver les elements connexes */
connex trouverConnexion (mat_t m, int n, int taille){
	int noeud = n;
	int* listeVu = malloc (USHRT_MAX*sizeof(*listeVu));
	int* stack = malloc (USHRT_MAX*sizeof(*stack));

	int sizeStk = 0;
	int sizeVu = 0;
	
	connex co;
	co.liste = malloc (USHRT_MAX*sizeof(*co.liste));

	while(1){
		for (int i = 0; i < taille; ++i) {
			if (m.m[noeud][i] > 0){
				if (repetition(listeVu, i, sizeVu) == 0){
					stack[sizeStk] = i;
					sizeStk++;
					listeVu[sizeVu] = i;
					sizeVu++;

				}
			}
		}

		if (sizeStk == 0)
			break;
		
		noeud = stack[sizeStk-1];
		sizeStk--;
	}
	co.liste = listeVu;
	co.taille = sizeVu;
	if (realloc (co.liste, taille*sizeof(co.liste)) == NULL)
		printf("error\n");
	return co;
}

void afficheConnexion (connex co, int noeud){
	printf("Connexion à %d:\n", noeud+1);
	for (int i = 0; i < co.taille; ++i){
		printf("%d ", co.liste[i]+1);
	}
	printf("\n");
}



/* recherche en profondeur sur les 1er noeuds connexe à la racine pour trouver les cicles  */
connex connexionForCycle (mat_t m, int n, int racine, int taille){
	int noeud = n;
	int* listeVu = malloc (USHRT_MAX*sizeof(*listeVu));
	int* stack = malloc (USHRT_MAX*sizeof(*stack));

	int sizeStk = 0;
	int sizeVu = 0;

	connex co;
	co.liste = malloc (USHRT_MAX*sizeof(*co.liste));
	co.liste[0] = n;
	co.taille = 1;
	while(1){
		for (int i = 0; i < taille; ++i) {
			if (m.m[noeud][i] > 0){
				if (repetition(listeVu, i, sizeVu) == 0){
					stack[sizeStk] = i;
					sizeStk++;
					listeVu[sizeVu] = i;
					sizeVu++;

				}
			}
		}
		if (sizeStk == 0)
			break;
		//printf("test%d\n", sizeStk);
		noeud = stack[sizeStk-1];
		co.liste[co.taille] = noeud;
		co.taille++;

		if (noeud == racine){
			if (realloc (co.liste, taille*sizeof(co.liste)) == NULL)
				printf("error\n");
			free (listeVu);
			free (stack);
			return co;
		}

		sizeStk--;
	}
	co.liste = NULL;
	co.taille = 0;
	return co;
}

void afficheCycle (connex* co, int noeud, int nbCo){
	for (int j = 0; j < nbCo ; j++){
		if (co[j].liste != NULL){
			printf("Cycle(s) de %d:\n",noeud+1);
			for (int i 	= 0; i < co[j].taille; ++i){
				printf("%d ", co[j].liste[i]+1);
			}
		}
	}
	printf("\n");
}

/* trouver les 1er noeud connexe à la racine */
void trouverCycle (mat_t m, int noeud, int taille){
	connex* co = malloc (USHRT_MAX*sizeof(*co));
	int nbCo = 0;
	for (int i = 0; i < taille; ++i){
		if (m.m[noeud][i] > 0){
			co[i] = connexionForCycle(m, i, noeud, taille);
			nbCo++;

		}
	}
	if (nbCo > 0)
		afficheCycle(co, noeud, nbCo);
	if (nbCo == 0)
		printf("Il n'y a pas de cycle\n");
}


