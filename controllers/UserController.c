#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../models/user.h"
void marquerPresence(char *fichier, char *matricule)
{
    // Ouvrir le fichier en mode d'ajout à la fin
    FILE *f = fopen(fichier, "a");
    if (f == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    time_t temps_actuel;
    struct tm *tm_info;
    time(&temps_actuel);
    tm_info = localtime(&temps_actuel);

    // Écrire dans le fichier le matricule, la date et l'heure
    fprintf(f, "%s|%04d|%02d|%02d|%02d|%02d|%02d\n", matricule, tm_info->tm_year + 1900,
            tm_info->tm_mon + 1, tm_info->tm_mday, tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec);

    printf("\n\n\x1b[32m**Presence marquee avec succes **\x1b[0m\n");

    fclose(f);
}

void listerClasses(char *fichier)
{
    FILE *f = fopen(fichier, "r");
    if (f == NULL)
    {
        printf("**Erreur d'ouverture du fichier %s.**\n", fichier);
        exit(1);
    }

    char ligne[100];
    while (fgets(ligne, sizeof(ligne), f) != NULL)
    {

        char *token = strtok(ligne, "|");
        while (token != NULL)
        {
            printf("%s\n", token);
            token = strtok(NULL, "|");
        }
    }

    fclose(f);
}

void listerEtudiantsParClasse(USER *etudiants, char *classe)
{
    USER *etudiantsParClasse = NULL;
    int j = 0;
    for (int i = 0; i < sizeof(etudiants); i++)
    {
        if (strcmp(classe, etudiants[i].classe) == 0)

        {
            etudiantsParClasse = realloc(etudiantsParClasse, (j + 1) * sizeof(USER));
            etudiantsParClasse[j] = etudiants[i];
            j++;
        }
    }

    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║           ETUDIANTS DE LA CLASSE: %s                         \n", classe);
    printf("╚══════════════════════════════════════════════════════════════╝\n");
    for (int i = 0; i < j; i++)
    {
        printf("║Matricule: %s     Nom: %s      Prenom: %s                      \n", etudiantsParClasse[i].matricule, etudiantsParClasse[i].nom, etudiantsParClasse[i].prenom);
    }
    printf("╚══════════════════════════════════════════════════════════════╝\n");
}

PRESENCE *lirePresence(char *fichier, int *nbPresences)
{
    FILE *f = fopen(fichier, "r");
    if (f == NULL)
    {
        printf("**Erreur d'ouverture du fichier d'Presences.**\n");
        exit(1);
    }

    PRESENCE *Presences = NULL;
    int nbLignes = 0;
    char ligne[150];
    while (fgets(ligne, sizeof(ligne), f))
    {
        PRESENCE SVG_PRESENCE;
        if (sscanf(ligne, "%[^|]|%d|%d|%d|%d|%d|%d\n",
                   SVG_PRESENCE.matricule,
                   &SVG_PRESENCE.date_presence.annee,
                   &SVG_PRESENCE.date_presence.mois,
                   &SVG_PRESENCE.date_presence.jour,
                   &SVG_PRESENCE.heure,
                   &SVG_PRESENCE.minute,
                   &SVG_PRESENCE.seconde) != EOF)
        {

            Presences = realloc(Presences, (nbLignes + 1) * sizeof(PRESENCE));

            Presences[nbLignes] = SVG_PRESENCE;
            nbLignes++;
        }
    }
    rewind(f);
    *nbPresences = nbLignes;
    fclose(f);

    return Presences;
}

void marquerPresenceAdmin(USER *fichierEtudiant, PRESENCE *fichierPresence, char *matricule, char *password)
{
    int estPresent = 0;
    int estMarque = 0;

    for (int i = 0; i < sizeof(fichierEtudiant); i++)
    {
        if (strcmp(fichierEtudiant[i].matricule, matricule) == 0)
        {
            estPresent = 1;
            break;
        }
    }

    if (estPresent)
    {
        time_t temps_actuel;
        struct tm *tm_info;
        time(&temps_actuel);
        tm_info = localtime(&temps_actuel);

        int jour_systeme = tm_info->tm_mday;
        int mois_systeme = tm_info->tm_mon + 1;

        if (fichierPresence != NULL)
        {
            for (int i = 0; i < sizeof(fichierPresence); i++)
            {
                PRESENCE SVG_PRESENCE = fichierPresence[i];
                if (strcmp(SVG_PRESENCE.matricule, matricule) == 0 && (SVG_PRESENCE.date_presence.jour == jour_systeme && SVG_PRESENCE.date_presence.mois == mois_systeme))
                {
                    printf("\n\n\x1b[31m**Vous avez déjà marqué pour aujourd'hui.**\x1b[0m\n");
                    estMarque = 1;
                    break;
                }
            }
        }

        if (estMarque == 0)
        {

            marquerPresence("database/presenceP.txt", matricule);
        }
    }
    else
    {
        printf("\n\n\x1b[31m**Matricule incorrect.**\x1b[0m\n");
        return;
    }

    if (fichierPresence != NULL)
    {
        free(fichierPresence);
    }
}
void marquerPresenceEtudiant(PRESENCE *fichierPresence, char *matricule, int nbPresences)
{
    int estMarque = 0;

    time_t temps_actuel;
    struct tm *tm_info;
    time(&temps_actuel);
    tm_info = localtime(&temps_actuel);

    int jour_systeme = tm_info->tm_mday;
    int mois_systeme = tm_info->tm_mon + 1;

    if (fichierPresence != NULL)
    {
        for (int i = 0; i < nbPresences; i++)
        {
            PRESENCE SVG_PRESENCE = fichierPresence[i];
            if (strcmp(SVG_PRESENCE.matricule, matricule) == 0 && (SVG_PRESENCE.date_presence.jour == jour_systeme && SVG_PRESENCE.date_presence.mois == mois_systeme))
            {
                printf("\n\n\x1b[31m**Vous avez déjà marqué votre présence pour aujourd'hui.**\x1b[0m\n");
                estMarque = 1;
                break;
            }
        }
    }

    if (!estMarque)
    {
        marquerPresence("database/presenceP.txt", matricule);
    }
     if (fichierPresence != NULL)
    {
        free(fichierPresence);
    }
}
