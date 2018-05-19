#ifndef MAT_H___
#define MAT_H___
#include "get_programme.h"

char* findOnlyOne (char* dest, char* src, int len);

struct matr {
  int n;
  int** m;
};
typedef struct matr mat_t;

struct connex {
	int taille;
	int* liste;
};
typedef struct connex connex;

mat_t initMat (int taille);
void afficheMat (mat_t m);
mat_t fillMat (char** all, char** one, int tailleAll, int tailleOne);
connex trouverConnexion (mat_t m, int n, int taille);
void afficheConnexion (connex liste, int noeud);

void trouverCycle (mat_t m, int n, int taille);


#endif
