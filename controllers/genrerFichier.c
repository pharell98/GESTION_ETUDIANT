#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/stat.h>
#include "../prototypes/prototypes.h"

void genererFpresence()
{
    int nbPresences, estPresent = 0, j = 0, nbEtudiants = 0;
    DATE *tabDate = NULL;
    DATE SVG_DATE;
    PRESENCE *Fpresence = lirePresence("database/presenceP.txt", &nbPresences);
    PRESENCE *PresenceParDate = NULL;

    if (Fpresence != NULL)
    {
        j = 0;
        for (int i = 0; i < nbPresences; i++)
        {
            SVG_DATE = Fpresence[i].date_presence;
            estPresent = 0;
            for (int k = 0; k < j; k++)
            {
                if (SVG_DATE.jour == tabDate[k].jour && SVG_DATE.mois == tabDate[k].mois && SVG_DATE.annee == tabDate[k].annee)
                {
                    estPresent = 1;
                    break;
                }
            }
            if (!estPresent)
            {
                tabDate = realloc(tabDate, (j + 1) * sizeof(DATE));
                tabDate[j].jour = SVG_DATE.jour;
                tabDate[j].mois = SVG_DATE.mois;
                tabDate[j].annee = SVG_DATE.annee;
                j++;
            }
        }
    }

    if (tabDate != NULL)
    {
        printf("╔════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                             LSITES DES PRESENCES PAR DATE                      ║\n");
        printf("╚════════════════════════════════════════════════════════════════════════════════╝\n");
        for (int i = 0; i < j; i++)
        {
            PRESENCE *Fpresences = lirePresence("database/presenceP.txt", &nbPresences);
            USER *Fetudiants = lireUsers("database/user.txt", &nbEtudiants);
            SVG_DATE = tabDate[i];
            listerEtudiantsParDate(Fetudiants, Fpresences, nbEtudiants, nbPresences, SVG_DATE);
        }
    }

    free(tabDate);
}


void listerEtudiantsParDate(USER *etudiants, PRESENCE *presence, int nbEtudiants, int nbPresences, DATE date)
{
    printf("╔════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║   LE  %02d/%02d/%04d                                                            \n", date.jour, date.mois, date.annee);
    printf("╚════════════════════════════════════════════════════════════════════════════════╝\n");
    int presenceTrouvee = 0;
    for (int i = 0; i < nbPresences; i++)
    {
        if (presence[i].date_presence.jour == date.jour && presence[i].date_presence.mois == date.mois && presence[i].date_presence.annee == date.annee)
        {
            for (int j = 0; j < nbEtudiants; j++)
            {
                if (strcmp(presence[i].matricule, etudiants[j].matricule) == 0)
                {
                    printf("║Matricule: %s   Nom: %s   Prenom: %s   Ref.: %s \n", etudiants[j].matricule, etudiants[j].nom, etudiants[j].prenom, etudiants[j].classe);
                    printf("╚════════════════════════════════════════════════════════════════════════════════╝\n");
                    presenceTrouvee = 1;
                    break;
                }
            }
        }
    }
    if (!presenceTrouvee)
    {
        printf("Aucun étudiant présent pour cette date.\n");
    }
}
