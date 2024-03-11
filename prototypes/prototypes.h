#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include "../models/user.h"

/* Fonction pour afficher l'interface de connexion */
void afficherInterface(USER *etuduiant, int nbUtilisateurs,char *matricule,int *type,char * nom,char * prenom,char * password);

/* Fonction pour lire les informations des Users depuis un fichier */
USER *lireUsers(char *fichier, int *nbUsers);
PRESENCE *lirePresence(char *fichier, int *nbPresences);

/* Fonction pour marquer une presence */
void marquerPresence(char *fichier, char *matricule);
void marquerPresenceAdmin(USER *fichierEtudiant, PRESENCE *fichierPresence, char *matricule, char *password);
void marquerPresenceEtudiant(PRESENCE *fichierPresence, char *matricule,int nbPresences);



/* Fonctions pour la saisie des informations de connexion */
void saisiUsername(char *username, size_t taille);
void saisiPassword(char *password);
int saisirInt(int min, int max, char msg[]);
void saisiChaine(char *chaine, size_t taille,char msg[]);


/* Fonction pour afficher le menu principal */
void afficherMenuPrincipal();

/* Fonction pour lister les classes */
void listerClasses(char *fichier);
void listerEtudiantsParClasse(USER *etudiants , char *classe);

/*GENERER FICHIER PRESENCE*/
//void genererFpresenceParDate(int jour, int mois, int annee);
void genererFpresence();
void listerEtudiantsParDate(USER *etudiants, PRESENCE *presence, int nbEtudiants, int nbPresences, DATE date);


/*MENU ETUDIANT ET ADMIN*/
int menuEtudiant();
int menuAdmin();


/*FONCTION ENVOI MESSAGE*/
void envoyerMessage(USER *fichierEtudiant, const char *matriculeDestinataire, const char *objet, const char *message);


#endif
