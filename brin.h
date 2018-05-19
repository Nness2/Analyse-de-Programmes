#ifndef BRIN_H___
#define BRIN_H___
#include "mat.h"

typedef short unsigned Shu;
struct noeud {
	int id;
	int* brins;
	int nbBrin;
};
typedef struct noeud noeud;

struct tabBrins{
	int* brins;
	int* noeuds;
	int* suivants;	
};
typedef struct tabBrins tabBrins;

mat_t numArrete(mat_t mat, int taille);
tabBrins tableauBrin(mat_t mat, int taille);
int nombreArrete (mat_t mat, int taille);
void afficheColonne (tabBrins tab, int taille);
connex trouverConnexionBrin (tabBrins tabB, int n, int taille);
void afficheConnexion_brin (connex co, int noeud);
void trouverCycle_brin (tabBrins tabB, int noeud, int t);

#endif