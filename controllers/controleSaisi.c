#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

void saisiUsername(char *username, size_t taille) {
    printf("║Nom d'utilisateur: ");
    fgets(username, taille, stdin);
    username[strcspn(username, "\n")] = '\0';

    while (strlen(username) == 0) {
        printf("Le nom d'utilisateur ne peut pas être vide. Veuillez réessayer : ");
        fgets(username, taille, stdin);
        username[strcspn(username, "\n")] = '\0';
    }
}

void saisiChaine(char *chaine, size_t taille, char msg[]) {
    puts("----------------------------------------------");
    puts(msg);
    fgets(chaine, taille, stdin);
    chaine[strcspn(chaine, "\n")] = '\0';

    while (strlen(chaine) == 0) {
        puts("----------------------------------------------\n");
        printf("Le champ ne peut pas être vide. Veuillez réessayer : \n");
        fgets(chaine, taille, stdin);
        chaine[strcspn(chaine, "\n")] = '\0';
    }
}




// Fonction pour masquer les caractères saisis par l'utilisateur
char *getPassword() {
    const char BACKSPACE = 127;
    const char RETURN = '\n';

    char *password = (char *)malloc(100); // Taille arbitraire du mot de passe
    int ch;
    int position = 0;

    // Masquer l'entrée
    struct termios old;
    tcgetattr(STDIN_FILENO, &old);
    struct termios new = old;
    new.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &new);

    while ((ch = getchar()) != RETURN) {
        if (ch == BACKSPACE) {
            if (position > 0) {
                printf("\b \b");
                position--;
            }
        } else {
            password[position++] = ch;
            printf("*");
        }
    }
    password[position] = '\0';

    // Restaurer les paramètres du terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &old);

    return password;
}

void saisiPassword(char *password) {
    printf("║Mot de passe: ");
    char *mdp = getPassword();
    strcpy(password, mdp);

    while (strlen(password) == 0) {
        printf("Le mot de passe ne peut pas être vide. Veuillez réessayer : ");
        mdp = getPassword();
        strcpy(password, mdp);
    }

    free(mdp); // Libérer la mémoire allouée pour le mot de passe
}


int saisirInt(int min, int max, char msg[])
{
    int x;
    do
    {
        puts(msg);
        scanf("%d", &x);
    } while (x < min || x > max);

    return x;
}