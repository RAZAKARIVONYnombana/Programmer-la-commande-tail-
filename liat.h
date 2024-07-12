#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIGNE 1000
#define DIX_LIGNES 10

int obtenir_nb_lignes(int argc, char *argv[]);
const char *obtenir_fichier(int argc, char *argv[]);
FILE *ouvrir_fichier(const char *fichier);
char **lire_lignes(FILE *f, int *nb_lignes, int lignes_a_afficher);
void afficher_derniere_lignes(char **lignes, int nb_lignes, int lignes_a_afficher);
