#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../models/user.h"

void envoyerMessage(USER *fichierEtudiant, const char *matriculeDestinataire, const char *objet, const char *message)
{
    int estPresent = 0;

    for (int i = 0; i < sizeof(fichierEtudiant); i++)
    {
        if (strcmp(fichierEtudiant[i].matricule, matriculeDestinataire) == 0)
        {
            estPresent = 1;
            break;
        }
    }

    if (estPresent)
    {
        FILE *fichier = fopen("database/messages.txt", "a+");

        if (fichier == NULL)
        {
            printf("Erreur lors de l'ouverture du fichier.\n");
            return;
        }

        time_t tempsActuel;
        struct tm *tempsInfo;
        time(&tempsActuel);
        tempsInfo = localtime(&tempsActuel);

        fprintf(fichier, "%02d|%02d|%04d|%02d|%02d|%02d|", tempsInfo->tm_mday, tempsInfo->tm_mon + 1,
                tempsInfo->tm_year + 1900, tempsInfo->tm_hour, tempsInfo->tm_min, tempsInfo->tm_sec);
        fprintf(fichier, "Matricule destinataire: %s|", matriculeDestinataire);
        fprintf(fichier, "Objet: %s|", objet);
        fprintf(fichier, "Message: %s|", message);
        fprintf(fichier, "État: Non lu\n");

        fclose(fichier);
    }
    else
    {
        printf("\n\n\x1b[31m**Matricule incorrect.**\x1b[0m\n");
        return;
    }
}
