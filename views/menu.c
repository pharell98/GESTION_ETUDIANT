#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../models/user.h"
#include "../prototypes/prototypes.h"

// Fonction pour afficher l'interface de connexion
void afficherInterface(USER *user, int nbUtilisateurs, char *matricule, int* type,char * nom,char * prenom,char * password)
{
    int i;
    int taille = 40;

    // Afficher un cadre et un titre
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║                     SE CONNECTER                ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");

    saisiUsername(matricule,taille);
    saisiPassword(password);
    printf("\n╚═════════════════════════════════════════════════╝\n");

    

    int trouve = 0;

    for (i = 0; i < nbUtilisateurs; i++)
    {
        if (strcmp(matricule, user[i].matricule) == 0 && strcmp(password, user[i].password) == 0)
        {
            trouve = 1;
            break;
        }
    }

    // Affichage d'un message de confirmation
    if (trouve)
    {
        strcpy(matricule, user[i].matricule);
        *type = user[i].type;
        strcpy(nom, user[i].nom);
        strcpy(prenom, user[i].prenom);
    }
    else
    {
        printf("\n\n\x1b[31m**Échec de la connexion. Veuillez réessayer.**\x1b[0m\n");
    }
}

#include <stdio.h>

int menuEtudiant()
{
    int choix;
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║                 Menu Étudiant                   ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    printf("║ 1 ==> Marquer Présence                          ║\n");
    printf("║ 0 ==> Deconnecter                               ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");

    do
    {
        printf("===========================\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);
        if (choix < 0 || choix > 1)
        {
            printf("Choix invalide! Veuillez saisir un choix entre 1 et 0.\n");
        }
        printf("===========================\n");
    } while (choix < 0 || choix > 1);

    return choix;
}

int menuAdmin()
{
    int choix;

    // Affichage du menu
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║                     Menu Admin                  ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    printf("║ 1 ==> Marquer présence                          ║\n");
    printf("║ 2 ==> Lister les classes                        ║\n");
    printf("║ 3 ==> Lister les étudiants d'une classe         ║\n");
    printf("║ 4 ==> Liste des présences des étudiants         ║\n");
    printf("║ 5 ==> Générer fichier presences d'une date      ║\n");
    printf("║ 6 ==> Générer fichier presences par Date        ║\n");
    printf("║ 7 ==> Envoyer un message                        ║\n");
    printf("║ 0 ==> Déconnexion                               ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");

    // Saisie du choix
    do
    {
        printf("===========================\n");
        printf("Entrez votre choix (1, 2, 3, 4, 5, 6 ou 0) : ");
        scanf("%d", &choix);

        // Validation du choix
        if (choix < 0 || choix > 6)
        {
            printf("Choix invalide ! Veuillez saisir un choix entre 1 et 6, ou 0 pour déconnexion.\n");
        }
    } while (choix < 0 || choix > 6);

    // Retour du choix
    return choix;
}

int menuMessage()
{
    int choix;

    // Affichage du menu
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║                     ENVOI MESSAGE               ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    printf("║ 1 ==> Message Specifique a un etudiant          ║\n");
    printf("║ 2 ==> Message tous les etudiants  de L'ecole    ║\n");
    printf("║ 3 ==> Message tous les etudiants d'une classe   ║\n");
    printf("║ 4 ==> Message a des etudiants choisis           ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");

    // Saisie du choix
    do
    {
        printf("===========================\n");
        printf("Entrez votre choix (1, 2, 3, 4) : ");
        scanf("%d", &choix);

        // Validation du choix
        if (choix < 1 || choix > 4)
        {
            printf("Choix invalide ! Veuillez saisir un choix entre 1 et 4.\n");
        }
    } while (choix < 1 || choix > 4);

    // Retour du choix
    return choix;
}

