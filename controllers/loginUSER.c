#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../models/user.h"

// Fonction pour lire les données des Users depuis un fichier//
USER *lireUsers(char *fichier, int *nbUsers)
{
    FILE *f = fopen(fichier, "r");
    if (f == NULL)
    {
        printf("**Erreur d'ouverture du fichier d'Users.**\n");
        exit(1);
    }

    USER *Users = NULL;
    int nbLignes = 0;
    char ligne[150];
    while (fgets(ligne, sizeof(ligne), f))
    {
        USER SVG_USER;
        if (sscanf(ligne, "%d|%[^|]|%[^|]|%[^|]|%d|%d|%d|%[^|]|%d|%[^|]|%[^|]|%s\n",
                   &SVG_USER.type,
                   SVG_USER.classe,
                   SVG_USER.nom,
                   SVG_USER.prenom,
                   &SVG_USER.date_naissance.jour,
                   &SVG_USER.date_naissance.mois,
                   &SVG_USER.date_naissance.annee,
                   SVG_USER.matricule,
                   &SVG_USER.age,
                   SVG_USER.adresse,
                   SVG_USER.genre,
                   SVG_USER.password) != EOF)

        {

            Users = realloc(Users, (nbLignes + 1) * sizeof(USER));

            Users[nbLignes] = SVG_USER;
            nbLignes++;
        }
    }
    
    rewind(f);

    *nbUsers = nbLignes; 
    fclose(f);

    return Users;
}

void listerEtudiantsParDATE(USER *etudiants, char *matricule)
{
    USER *etudiantsParmatricule = NULL;
    int j = 0;
    for (int i = 0; i < sizeof(etudiants); i++)
    {
        if (strcmp(matricule, etudiants[i].matricule) == 0)

        {
            etudiantsParmatricule = realloc(etudiantsParmatricule, (j + 1) * sizeof(USER));
            etudiantsParmatricule[j] = etudiants[i];
            j++;
        }
    }

    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║           ETUDIANTS DE LA matricule: %s                        \n", matricule);
    printf("╚══════════════════════════════════════════════════════════════╝\n");
    for (int i = 0; i < j; i++)
    {
        printf("║Matricule: %s     Nom: %s      Prenom: %s                  \n", etudiantsParmatricule[i].matricule, etudiantsParmatricule[i].nom, etudiantsParmatricule[i].prenom);
    }
    printf("╚══════════════════════════════════════════════════════════════╝\n");
}


