#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdio.h> 
#include <limits.h>
#include "mat.h"
#include "brin.h"

/* trouve le nombre d'arrete */
int nombreArrete (mat_t mat, int taille){   //trouve le nombre d'arrete
	int cmpArrete = 0;
	for (int i = 0; i < taille; ++i){
		for (int j = 0; j < taille; ++j){
			if (mat.m[i][j] > 0)
				cmpArrete ++;
		}
	}
	return cmpArrete;
}

/* donne un poid à chaque arrete */
mat_t numArrete(mat_t mat, int taille) {    //numerote le arrete
	 mat_t m;
	int numArt = 1;
	for (int i = 0; i < taille; ++i){
		for (int j = 0; j < taille; ++j){
			if (m.m[i][j] == 1){
				m.m[i][j] = numArt;
				numArt++;
			}
		}
	}
	return m;
}


/* rempli la liste des brins de la structure */
int* colonne1 (int nbArt){
	int nbColonne = (nbArt*2)+1;
	int* tab = malloc (nbColonne*sizeof(*tab));
	int j = 1;
	tab[nbColonne/2] = 0;
	for (int i = (nbColonne/2)+1 ; i < nbColonne ; i++){
		tab[i] = j;
		j++;
	}
	j = nbArt;
	for (int i = 0 ; i < nbArt ; i++){
		tab[i] = j*-1;
		j--;
	}
	return tab;
}

/* rempli la liste des noeuds de la structure */
int* colonne2 (noeud* n, int* col1, int taille, int nbColonne){
	int* col2 = malloc(nbColonne*sizeof(*col2));
	for (int i = 0; i < taille ; ++i){
		for (int j = 0; j < n[i].nbBrin ; ++j){
			for (int k = 0; k < nbColonne; k++){
				if(n[i].brins[j] == col1[k]){
					col2[k] = i+1; 
					break;
				}
			}
		}
	}

	col2[nbColonne/2] = 0;
	//afficheNoeud(n,taille);
	return col2;
}


/* trouve le brin suivant selon le noeud et le brin correspondant */
int findSuivant (int* brins, int courant, int taille){
	int suivant;
	int i;
	for (i = 0; i < taille; ++i) {
		if(courant == brins[i]){
			suivant = brins[i+1];
			if (i == taille-1)
				suivant = brins[0];
			return suivant;
		}
	}

	return suivant;
}

/* rempli la liste des brins suivant de la structure */
int* colonne3 (noeud* n, int* col1, int* col2, int taille, int nbColonne){
	int* col3 = malloc(nbColonne*sizeof(*col3));
	for (int i = 0; i < nbColonne ; ++i){
		for (int j = 0 ; j < n[col2[i]-1].nbBrin ; j++){
			if (col2[i] != 0){
				if (n[col2[i]-1].brins[j] == col1[i])
					col3[i] = findSuivant (n[col2[i]-1].brins, col1[i], n[col2[i]-1].nbBrin);
			}
		}
	}
	return col3;
}
	
/* trouve le nombre de brin attaché à chaque noeud */
int nombreBrinsParNoeud(mat_t m,int taille, int i){   //trouvel le nombre de brin par noeud
	int cmp = 0;
	for (int k = 0; k < taille; ++k){
		if (m.m[i][k] > 0)
			cmp++;
	}
	for (int k = 0; k < taille; ++k){
		if (m.m[k][i] > 0)
			cmp++;
	}

	return cmp;
}

/* remplis ma structure noeud avec tout les brins correspondant à chaque noeud je m'en sert notament pour trouver le 1er brin d'un noeud et tourner autour  */
noeud* fillStructNoeud (mat_t m, int taille){ // prend matrice avec arrete numerote
	noeud* n = malloc(taille* sizeof(*n));

	for (int i = 0; i < taille; ++i){
			n[i].id = i+1;
			n[i].nbBrin = nombreBrinsParNoeud(m, taille, i);
			n[i].brins = malloc (n[i].nbBrin*sizeof(*n[i].brins));
		
	}

	for (int i = 0; i < taille; ++i){
		for (int j = 0; j < taille; ++j){
			if (m.m[i][j] > 0){
				if(n[i].nbBrin > 0){
					n[i].brins[n[i].nbBrin-1] = (m.m[i][j])*-1; 
					n[i].nbBrin--;
					n[j].brins[n[j].nbBrin-1] = m.m[i][j]; 
					n[j].nbBrin--;
				}
			}
		}
	}

	for (int i = 0; i < taille; ++i)
		n[i].nbBrin = nombreBrinsParNoeud(m, taille, i);

	return n;
}


int afficheNoeud (noeud* n, int taille){
	for (int i = 0; i < taille; ++i){
		printf("n%d: ", i);
		for (int j = 0; j < n[i].nbBrin ; ++j)
			printf("%d ", n[i].brins[j]);
		printf("\n");
	}
}

void afficheColonne (tabBrins tab, int taille){
	int colonnes = (taille*2)+1;
	for (int i = 0; i < colonnes; ++i)
	{
		printf("%d | %d | %d\n", tab.brins[i], tab.noeuds[i], tab.suivants[i]);
	}
	printf("\n");
}

/* remplis ma structure tabBrins */
tabBrins tableauBrin (mat_t m, int taille){
	printf("\n");
	tabBrins table;

	int nbrArrete = nombreArrete(m, taille);
	noeud* n = fillStructNoeud(m, taille);
	int colonne = (nombreArrete(m,taille)*2)+1;
	
	table.brins = colonne1(nbrArrete);
	table.noeuds = colonne2(n,table.brins,taille,colonne);
	table.suivants = colonne3(n, table.brins, table.noeuds, taille, colonne);

	return table;
}







/* meme chose que les algos de recherche de connextion et de cycle de mat mais readapté pour brin */
int repetition_brin (int* liste, int e, int taille){
	for (int i = 0; i < taille; ++i){
		if (liste[i] == e)
			return 1;
	}
	return 0;
}

int noeudSuiv (tabBrins tabB, int position, int taille){
	int invNext = tabB.suivants[position]*-1;
	for (int i = 0; i < taille; ++i) {
		if (tabB.brins[i] == invNext){
			return tabB.noeuds[i];
		}
	}
	return 0;
}

connex trouverConnexionBrin (tabBrins tabB, int n, int t){
	int taille = (t*2)+1;
	int noeud = n;
	int* listeVu = malloc (USHRT_MAX*sizeof(*listeVu));
	int* stack = malloc (USHRT_MAX*sizeof(*stack));

	int sizeStk = 0;
	int sizeVu = 0;
	
	connex co;
	co.liste = malloc (USHRT_MAX*sizeof(*co.liste));

	while(1){
		for (int i = 0; i < taille; ++i) {
			if (tabB.noeuds[i] == noeud){
				if (tabB.suivants[i] < 0){
					if (repetition_brin(listeVu, noeudSuiv (tabB, i, taille), sizeVu) == 0){
						stack[sizeStk] = noeudSuiv (tabB, i, taille);
						sizeStk++;
						listeVu[sizeVu] = noeudSuiv (tabB, i, taille);
						sizeVu++;
					}
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


void afficheConnexion_brin (connex co, int noeud){
	printf("Connexion à %d:\n", noeud);
	for (int i = 0; i < co.taille; ++i){
		printf("%d ", co.liste[i]);
	}
	printf("\n");
}





connex connexionForCycle_brin (tabBrins tabB, int n, int racine, int t){
	int taille = (t*2)+1;
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
			if (tabB.noeuds[i] == noeud){
				if (tabB.suivants[i] < 0){
					if (repetition_brin(listeVu, noeudSuiv (tabB, i, taille), sizeVu) == 0){
						stack[sizeStk] = noeudSuiv (tabB, i, taille);
						sizeStk++;
						listeVu[sizeVu] = noeudSuiv (tabB, i, taille);
						sizeVu++;
					}
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

void afficheCycle_brin (connex* co, int noeud, int nbCo){
	for (int j = 0; j < nbCo ; j++){
		if (co[j].liste != NULL){
			printf("Cycle(s) de %d:\n",noeud);
			for (int i 	= 0; i < co[j].taille; ++i){
				printf("%d ", co[j].liste[i]);
			}
		}
	}
	printf("\n");
}


void trouverCycle_brin (tabBrins tabB, int noeud, int t){
	int taille = (t*2)+1;
	connex* co = malloc (USHRT_MAX*sizeof(*co));
	int nbCo = 0;
	for (int i = 0; i < taille; ++i){
		if (tabB.noeuds[i] == noeud){
			if (tabB.suivants[i] < 0){
				co[i] = connexionForCycle_brin(tabB, noeudSuiv (tabB, i, taille), noeud, taille);
				nbCo++;
			}
		}
	}
	if (nbCo > 0)
		afficheCycle_brin(co, noeud, nbCo);
	if (nbCo == 0)
		printf("Il n'y a pas de cycle\n");
}

