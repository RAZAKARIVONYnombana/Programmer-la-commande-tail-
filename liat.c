#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liat.h"

#define DIX_LIGNES 10

// Fonction principale
int main(int argc, char *argv[]) {
    // Obtenez le nombre de lignes à afficher depuis les arguments ou utilisez la valeur par défaut
    int lignes_a_afficher = obtenir_nb_lignes(argc, argv);

    // Obtenez le nom du fichier à ouvrir depuis les arguments
    const char *fichier = obtenir_fichier(argc, argv);

    // Ouvrez le fichier et gérez les erreurs d'ouverture
    FILE *f = ouvrir_fichier(fichier);

    // Lire toutes les lignes et compter le nombre total de lignes
    int nb_lignes;
    char **lignes = lire_lignes(f, &nb_lignes, lignes_a_afficher);

    // Afficher les dernières lignes
    afficher_derniere_lignes(lignes, nb_lignes, lignes_a_afficher);

    fclose(f);
    return 0;
}

// Fonction pour obtenir le nombre de lignes à partir des arguments
int obtenir_nb_lignes(int argc, char *argv[]) {
    int lignes_a_afficher = DIX_LIGNES;
    if (argc > 2 && strcmp(argv[1], "-n") == 0) {
        lignes_a_afficher = strtol(argv[2], NULL, 10);
        if (lignes_a_afficher <= 0) {
            fprintf(stderr, "Nombre de lignes invalide : %s\n", argv[2]);
            exit(1);
        }
    }
    return lignes_a_afficher;
}

// Fonction pour obtenir le nom du fichier à partir des arguments
const char *obtenir_fichier(int argc, char *argv[]) {
    if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'n') {
        return argv[3];  // Le fichier est après le nombre de lignes
    } else {
        return argv[1];  // Le fichier est le premier argument après le nom du programme
    }
}

// Fonction pour ouvrir le fichier et gérer les erreurs
FILE *ouvrir_fichier(const char *fichier) {
    FILE *f = fopen(fichier, "r");
    if (f == NULL) {
        fprintf(stderr, "ERREUR D'OUVERTURE DU FICHIER\n");
        exit(1);
    }
    return f;
}

// Fonction pour lire toutes les lignes du fichier dans un tableau
char **lire_lignes(FILE *f, int *nb_lignes, int lignes_a_afficher) {
    char **lignes = (char **)malloc(lignes_a_afficher * sizeof(char *));
    if (lignes == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(1);
    }

    for (int i = 0; i < lignes_a_afficher; i++) {
        lignes[i] = (char *)malloc(MAX_LIGNE * sizeof(char));
        if (lignes[i] == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire\n");
            exit(1);
        }
    }

    int i = 0;
    *nb_lignes = 0;
    while (fgets(lignes[i], MAX_LIGNE, f) != NULL) {
        i = (i + 1) % lignes_a_afficher;
        (*nb_lignes)++;
    }

    return lignes;
}

// Fonction pour afficher les dernières lignes du fichier
void afficher_derniere_lignes(char **lignes, int nb_lignes, int lignes_a_afficher) {
    int debut = nb_lignes < lignes_a_afficher ? 0 : (nb_lignes % lignes_a_afficher);
    for (int i = 0; i < lignes_a_afficher && i < nb_lignes; i++) {
        printf("%s", lignes[(debut + i) % lignes_a_afficher]);
    }
}
