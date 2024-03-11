#ifndef ETUDIANT_H
#define ETUDIANT_H

typedef struct{
    int jour;
    int mois;
    int annee;
}DATE;

typedef struct
{
    int type;
    char classe[50];
    char nom[50];
    char prenom[50];
    DATE date_naissance;
    char matricule[50];
    int age;
    char adresse[100];
    char genre[10];
    char password[50];
} USER;



typedef struct
{
    char matricule[50];
    DATE date_presence;
    int heure;
    int minute;
    int seconde;
} PRESENCE;



#endif