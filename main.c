#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "prototypes/prototypes.h"

int main()
{

    char ok;
    int choix;
    do
    {
        ok = 'p';
        int type = 0;
        int taille = 40;
        int nbUsers;
        char matricule[40];
        char matricule1[40];
        char classe[20];
        char nom[20];
        char password[20];
        char password1[20];
        char prenom[20];
        int nbPresences;
        char matriculeDestinataire[50];
        char objet[100];
        char message[1000];
        /*
         saisiChaine(matriculeDestinataire, sizeof(matriculeDestinataire), "Entrez le matricule de l'étudiant : ");
        saisiChaine(objet, sizeof(objet), "Saisir Objet");
        saisiChaine(message, sizeof(message), "Saisir Message");
        */

        USER *Users = lireUsers("database/user.txt", &nbUsers);
        PRESENCE *Presences = lirePresence("database/presenceP.txt", &nbPresences);

        // envoyerMessage(Users, matriculeDestinataire, objet, message);

        afficherInterface(Users, nbUsers, matricule, &type, nom, prenom, password);

        if (type == 1)
        {
            do
            {
                choix = menuEtudiant();
                switch (choix)
                {
                case 1:
                    PRESENCE *Presences = lirePresence("database/presenceP.txt", &nbPresences);
                    marquerPresenceEtudiant(Presences, matricule, nbPresences);
                    break;
                case 0:
                    ok = 'o';
                    getchar();
                    break;
                }
            } while (choix != 0);
        }
        else if (type == 2)
        {
            do
            {
                choix = menuAdmin();
                switch (choix)
                {
                case 1:
                
                    getchar();
                    while (1)
                    {

                        PRESENCE *Presences = lirePresence("database/presenceP.txt", &nbPresences);
                        puts("Appuyer sur Q pour quitter\n");
                        saisiUsername(matricule1, taille);
                        if (strcmp(matricule1, "q") == 0 || strcmp(matricule1, "Q") == 0)
                        {
                            saisiPassword(password1);
                            puts("");
                            if (strcmp(password, password1) == 0)
                            {
                                break;
                            }
                        }
                        else
                        {
                            marquerPresenceAdmin(Users, Presences, matricule1, password1);
                        }
                    }
                    
                    break;
                case 5:
                   /* DATE date;
                    date.jour = saisirInt(1, 31, "entrez le jour");
                    puts("------------------------------------");
                    date.mois = saisirInt(1, 12, "entrez le mois");
                    puts("------------------------------------");
                    date.annee = saisirInt(1, 2024, "entrez l'année");
                    listerEtudiantsParDate(Users, Presences, nbUsers, nbPresences, date);
                    puts("------------------------------------");
                    
                    */
                    break;
                case 6:
                   // genererFpresence();
                    
                    break;

                default:
                    break;
                }
            } while (choix != 0);
        }

        while (ok != 'n' && ok != 'N' && ok != 'o' && ok != 'O')
        {
            printf("Voulez-vous continuer (O/N) ? ");
            scanf(" %c", &ok);
            if (ok != 'n' && ok != 'N' && ok != 'o' && ok != 'O')
            {
                printf("Veuillez ressayer !\n");
            }
            getchar();
        }
        free(Users);
    } while (ok != 'n' && ok != 'N');

    if (ok == 'n' || ok == 'N')
    {
        puts("Au revoir !");
    }

    return 0;
}
