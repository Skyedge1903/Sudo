#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define BORD 9

int alea(int bord);
int initialize(int bord, int grille[][bord]);
int vide(int bord, int grille[][bord]);
int vide_2(int bord, int grille[][bord]);
int grille_ok(int bord, int grille[][bord]);
void print(int bord, int grille[][bord] ,int x ,int z);
int generation(int bord, int grille[][bord]);
int supprime(int difficulte, int bord ,int grille[][bord]);
int difficulte();
void jouer(int bord, int grille[][bord], int solution[][bord], int * score);
int sauvegarder(int bord, char * nom, int grille[][bord]);
int lire(int bord, char * nom, int grille[][bord]);

int main()
{
    system("color 0a");
    int stop = 1;
    int a = 0;
    srand(time(NULL));
    int tableau[BORD][BORD];
    initialize(BORD, tableau);
    int soluce[BORD][BORD];
    initialize(BORD, soluce);
    char str[100];
    char input[100];
    int score = 0;
    int score_[1][1];
    int table_score[10][1];
    //int table_score[10][1] = {0,0,0,0,0,0,0,0,0,0};
    //sauvegarder(10, "top_score.t", table_score);

    while (stop) {

        do {
            printf("MENU PRINCIPAL \n \n");
            printf("1 - Lancer la grille chargee \n");
            printf("2 - Generer une grille \n");
            printf("3 - Reprendre une grille \n");
            printf("4 - Enregistrer la grille en cours \n");
            printf("5 - Supprimer une grille \n");
            printf("6 - Tableau des scores \n");
            printf("7 - Menu d'aide \n");
            printf("8 - Quitter \n \n");
            printf("Votre choix : ");

            a = getchar( ) - '0';
            system("cls");

        } while (!(a >=1 && a <=8));

        switch (a) {

            case 1 :

                if (!vide_2(BORD , tableau)) jouer(BORD, tableau, soluce, &score);
                else printf("Pas de grille chargee \n");
                break;

            case 2 :

                initialize(BORD, tableau);
                while (!vide(BORD, tableau)) generation(BORD, tableau);
                initialize(BORD, soluce);
                for (int i = 0 ; i< BORD ; i++) {
                    for (int y = 0 ; y < BORD ; y ++) {
                        soluce[i][y]=tableau[i][y];
                    }
                }
                supprime(difficulte(), BORD , tableau);
                print(BORD, tableau, -1 ,-1);
                score = 0;
                break;

            case 3 :

                initialize(BORD, tableau);
                system("dir /A-D /B *.o");
                printf("Entrez le nom de la grille a lancer : ");
                scanf("%s", str);
                int longeur = strlen(str);
                str[longeur] = '.';
                str[longeur + 1] = 'o';
                str[longeur + 2]='\0';
                lire(BORD, str, tableau);
                print(BORD, tableau, -1 ,-1);
                str[longeur + 1] = 's';
                lire(BORD, str, soluce);
                str[longeur + 1] = 'p';
                lire(BORD, str, score_);
                score = score_[0][0];
                printf("\n");
                printf("Score de la grille : %d \n", score);
                break;

            case 4 :

                printf("Entrez un nom pour votre grille : ");
                scanf("%s", str);
                int taille = strlen(str);
                str[taille] = '.';
                str[taille + 1] = 'o';
                str[taille + 2]='\0';
                sauvegarder(BORD, str, tableau);
                str[taille + 1] = 's';
                sauvegarder(BORD, str, soluce);
                str[taille + 1] = 'p';
                score_[0][0] = score;
                sauvegarder(BORD, str, score_);
                break;

            case 5 :

                system("dir /A-D /B *.o");
                printf("Entrez 'current' pour supprimer la grille en cours, \n");
                printf("Entrez 'all' pour tout supprimer, \n");
                printf("Entrez le nom de la grille a supprimer : ");
                scanf("%s", input);
                if (!strcmp(input, "current")) initialize(BORD, tableau);
                else if (!strcmp(input, "all")) {
                        system("del *.o");
                        system("del *.s");
                        system("del *.p");
                }
                else {
                    str[0] = 'd';
                    str[1] = 'e';
                    str[2] = 'l';
                    str[3] = ' ';
                    str[4] = '\0';
                    strcat(str, input);
                    strcat(str, ".*");
                    system(str);
                }
                break;

            case 6 :

                printf("Tableau des records \n\n");
                lire(10, "top_score.t", table_score);
                for (int i = 0 ; i < 10 ; i++) {
                    printf("%d\n", table_score[i][0]);
                }
                printf("\n");
                break;

            case 7 :

                printf("A vous de tester ;)\n\n");
                printf("Un exemple : x:y : 1:1 : Premiere case du sudoku\n\n");
                printf("Pour quitter en partie lancer l'aide : 0:0 \n\n");

                break;

            case 8 :

                stop = 0;
                break;
        }

        system("pause");
        system("cls");


}
    return 0;
}
