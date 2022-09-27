#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// Générateur de chiffre aléatoire
int alea(int bord) {
    int nb_alea;
    nb_alea = (rand() % bord) + 1;
    return nb_alea;
}
// Prototype de la fonction d'initialisation
int initialize(int bord, int grille[][bord]);
// Fonction de vérification d'initialisation
int initialize(int bord, int grille[][bord]) {
    for (int j = 0 ; j < bord ; j++) {
        for (int i =0 ; i < bord ; i++) {
            grille[j][i]=0;
        }
    }
}

int sauvegarder(int bord, char * nom, int grille[][bord]) {
    FILE* f = fopen(nom, "w");
    if(f == NULL) return 0;
    else{
        for(int i = 0; i < bord; i++){
            fwrite(grille[i], sizeof(int), bord, f);
        }
        fclose(f);
    }
    return 0;
}


int lire(int bord, char * nom, int grille[][bord]) {
    FILE* f = fopen(nom, "r");
    if(f == NULL) return 0;
    else{
        for(int i = 0; i < bord; i++){
            fread(grille[i], sizeof(int), bord, f);
        }
        fclose(f);
    }
    return 1;
}


// Prototype de la fonction vide?
int vide(int bord, int grille[][bord]);
// Fonction de vérification vide?
int vide(int bord, int grille[][bord]) {
    for (int j = 0 ; j < bord ; j++) {
        for (int i =0 ; i < bord ; i++) {
            if (grille[j][i]>bord+1 || grille[j][i]<=0) return 0;
        }
    }
    return 1;
}
// Prototype de la fonction vide?
int vide_2(int bord, int grille[][bord]);
// Fonction de vérification vide?
int vide_2(int bord, int grille[][bord]) {
    for (int j = 0 ; j < bord ; j++) {
        for (int i =0 ; i < bord ; i++) {
            if (grille[j][i]==bord+1) return 0;
        }
    }
    return 1;
}
// Prototype de la fonction de vérification de grille
int grille_ok(int bord, int grille[][bord]);
// Fonction de vérification de grille
int grille_ok(int bord, int grille[][bord])
{
    int tab_verif [bord];
    for (int i = 0 ; i < bord ; i++) tab_verif [i] = 0;

    // veriffication des lignes (ok si les valeurs de 1 à 9 sont trouvées)
    for (int i = 0 ; i < bord ; i++) {
        for (int j = 0 ; j < bord ; j++) {
            if (tab_verif[grille[i][j]-1]>bord+1) {
                tab_verif[grille[i][j]-1-(bord+1)]++;
            } else tab_verif[grille[i][j]-1]++;
        }
        for (int j = 0 ; j < bord ; j++) if (tab_verif[j]==2) return 0;
        for (int j = 0 ; j < bord ; j++) tab_verif [j] = 0;
    }

    // veriffication des colonnes (ok si les valeurs de 1 à 9 sont trouvées)
    for (int i = 0 ; i < bord ; i++) {
        for (int j = 0 ; j < bord ; j++) {
            if (tab_verif[grille[j][i]-1]>bord+1) {
                tab_verif[grille[j][i]-1-(bord+1)]++;
            } else tab_verif[grille[j][i]-1]++;
        }
        for (int j = 0 ; j < bord ; j++) if (tab_verif[j]==2) return 0;
        for (int j = 0 ; j < bord ; j++) tab_verif [j] = 0;
    }

    // veriffication des sous tableau (ok si les valeurs de 1 à 9 sont trouvées)
    int root = sqrt((float) bord);
    for (int h = 0 ; h < root ; h ++) {
        for (int i = 0 ; i < root ; i ++) {
            for (int j = 0 ; j < root ; j++) {
                for (int k = 0 ; k < root ; k++) {
                    if (tab_verif[grille[j+h*root][k+i*root]-1]>bord+1){
                        tab_verif[grille[j+h*root][k+i*root]-1-(bord+1)]++;
                    } else tab_verif[grille[j+h*root][k+i*root]-1]++;
                }
            }
            for (int j = 0 ; j < bord ; j++) if (tab_verif[j]==2) return 0;
            for (int j = 0 ; j < bord ; j++) tab_verif [j] = 0;
        }
    }
    return 1;
}
// Prototype de la fonction d'affichage
void print(int bord, int grille[][bord] ,int x ,int z);
// Fonction d'affichage de la grille
void print(int bord, int grille[][bord] ,int x ,int z)
{
    int root = sqrt((float) bord);
    for (int y = 0 ; y < bord ; y++) {
        if (y % root == 0) printf("  ");
        printf("%d ", y+1);
    }
    printf("\n");
    for (int i = 0 ; i < bord ; i++) {
        if (i % root == 0 ) {
            for (int y = 0 ; y < (bord+root)*2-1 ; y++) {
                if (y == 0) printf(" ");
                printf("-");
            }
            printf("\n");
        }
        for (int y = 0 ; y < bord ; y++) {
            if (y % root == 0) printf ("| ");
            if (y==x-1 && z-1==i) printf("X ");
            else if (grille[i][y] <= bord && grille[i][y] >= 1) printf("%d ", grille[i][y]);
            else if (grille[i][y] == bord+1 ) printf("  ");
            else if (grille[i][y] > bord+1) printf("%d ", grille[i][y]-(bord+1));
            if (y == bord-1) printf("| %d",i+1);
        }
        printf("\n");
    }
    for (int y = 0 ; y < (bord+root)*2-1 ; y++) {
        if (y == 0) printf(" ");
        printf("-");
    }
    printf("\n");
}
// Prototype de la fonction de generation de grille
int generation(int bord, int grille[][bord]);
// Fonction de generation de grille
int generation(int bord, int grille[][bord])
{
    initialize(bord, grille);
    int tabl_alea [bord];
    for (int i = 0 ; i < bord ; i++) tabl_alea [i]=i+1;
    int inter;
    int x;
    int y;
    for (int i =0 ; i < bord ; i++) {
        for (int j = 0 ; j < bord ; j++) {
            // melange aléatoire du tableau
            for (int l = 0 ; l < bord ; l++) {
                x = alea(bord)-1;
                y = alea(bord)-1;
                inter = tabl_alea[x];
                tabl_alea[x] = tabl_alea[y];
                tabl_alea[y] = inter;
            }
            for (int k = 0 ; k < bord ; k++) {
                grille[i][j]=tabl_alea[k];
                if (grille_ok(bord, grille)) break;
            }
            if (!grille_ok(bord, grille)) return 0;
        }
    }
}
// Prototype de la fonction qui supprime des cases
int supprime(int difficulte, int bord ,int grille[][bord]);
// Fonction qui supprime des cases de la grille
int supprime(int difficulte, int bord ,int grille[][bord])
{
    difficulte = difficulte*18;
    int aleax;
    int aleay;
    for (int i = 0 ; i< difficulte ; i ++) {
        aleax = alea(bord)-1;
        aleay = alea(bord)-1;
        if (grille[aleax][aleay] != bord+1) grille[aleax][aleay] = bord+1;
        else difficulte++;
    }
}
// Fonction de saisie de la difficutlté
int difficulte() {
    int difficulte_var;
    printf("Entrez la difficultee (1,2,3) : \n");
    do {
        difficulte_var = getchar( ) - '0';
    } while (!(difficulte_var >=1 && difficulte_var <=3));
    system("cls");
    return(difficulte_var);
}

int modif(int bord, int tableau[][bord], int x , int y) {
    if (tableau[y-1][x-1] > bord+1) {
        return 1;
    }
    else return 0;
}

int aide(int bord, int tableau[][bord], int solution[][bord], int * score) {

    int a = 0;
    int x = -1;
    int y = -1;
    int table_score[10][1] = {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}};

    do {
        system("cls");
        printf("Menu Aide : \n \n");
        printf("1 - Validation d'une case de la grille \n");
        printf("2 - Donner une case de la grille \n");
        printf("3 - Validation grille \n");
        printf("4 - Menu Principal \n\n");
        printf("Votre choix : ");
        a = getchar( ) - '0';
        system("cls");
    } while (!(a >=1 && a <=4));

    switch (a) {

        case 1:

            while (x>bord || y>bord || x<1 || y<1 || !(tableau[y-1][x-1]>bord+1)) {
                if (!(tableau[y-1][x-1]>bord)) {
                    x=-1;
                    y=-1;
                }
                print(bord, tableau , x , y);
                printf("\n");
                printf("x:y : ");
                scanf("%d:%d",&x , &y);
                system("cls");
            }
            if (solution[y-1][x-1]==tableau[y-1][x-1]-(bord+1)) {
                tableau[y-1][x-1] = solution[y-1][x-1];
                printf("C'est une bonne reponse \n");
                system("pause");
                system("cls");
            } else {
                tableau[y-1][x-1] = bord+1;
                printf("C'est une mauvaise reponse \n");
                system("pause");
                system("cls");
            }
            * score = * score - 25;
            break;

        case 2:

            if (!vide_2(bord,tableau)) {
                int aleax;
                int aleay;
                do {
                    aleax = alea(bord)-1;
                    aleay = alea(bord)-1;
                } while (tableau[aleax][aleay]!=bord+1);
                print(bord, tableau , aleay+1 , aleax+1 );
                system("pause");
                system("cls");
                tableau[aleax][aleay] = solution[aleax][aleay];
                print(bord, tableau , -1 , -1);
                system("pause");
                system("cls");
                * score = * score - 50;
            } else {
                printf("Plus aucune case vide ! \n");
                system("pause");
                system("cls");
            }
            break;

        case 3:

            if (!vide_2(bord,tableau)) {
                printf("Il reste des cases vides ! \n");
                system("pause");
                system("cls");
            } else {
                if (!grille_ok(bord,tableau)) {
                    * score = * score - 25;
                    for (int i =0 ;i < bord ; i++) {
                        for (int j = 0 ; j < bord ; j ++) {
                            if (solution[i][j]!=tableau[i][j]-(bord+1) && tableau[i][j]>bord+1) {
                                * score = * score - 25;
                            }
                        }
                    }
                    printf("La grille est fausse ! \n");
                    system("pause");
                    system("cls");
                } else {
                    * score = * score + 1000;
                    printf("Bravo vous avez gagne ! \n");
                    system("pause");
                    system("cls");
                    lire(10, "top_score.t", table_score);
                    printf("Ecriture score \n");
                    system("pause");
                    for (int i = 0 ; i < 10 ; i++) {
                        table_score[i][0];
                        /*if (table_score[i][0] < *score) {
                            table_score[i][0] = *score;
                            break;
                        }
                        */
                    }
                    printf("Ecriture score ok \n");
                    system("pause");
                    sauvegarder(10, "top_score.t", table_score);
                    printf("Suavegarde ok \n");
                    system("pause");
                    return 1;
                }
            }
            break;

        case 4:

            return 1;
            break;
    }

    return 0;
}

void jouer(int bord, int tableau[][bord], int solution[][bord], int * score) {
    int x = -1;
    int y = -1;
    int substitue = 0;
    int stop = 0;

    do {
            while (x>bord || y>bord || x<1 || y<1 || !(tableau[y-1][x-1]>bord)) {
                if (!(tableau[y-1][x-1]>bord)) {
                    x=-1;
                    y=-1;
                }
                printf("Score : %d \n", *score);
                printf("Aide : 0:0 \n \n");
                print(bord, tableau , x , y);
                printf("\n");
                printf("x:y : ");
                scanf("%d:%d",&x , &y);
                if (x == 0 && y == 0) {
                    stop = aide(bord, tableau, solution, score);
                    printf("stop = %d", stop);
                    system("pause");
                    if (stop) {
                        printf("quitte boucle");
                        system("pause");
                        system("cls");
                        break;
                    }
                    x = -1;
                    y = -1;
                }
                else {
                    if (modif(bord, tableau, x, y)) *score = *score - 10;
                    system("cls");
                }
            }
            if (stop) break;

            while (substitue>bord || substitue<1 ){
                printf("Score : %d \n", *score);
                printf("Aide : X \n \n");
                fflush(stdout);
                print(bord, tableau , x , y);
                printf("X = ");
                scanf("%d",&substitue);
                system("cls");
            }

            printf("Break 3");
            fflush(stdout);
            tableau[y-1][x-1]=substitue+(bord+1);
            x = -1;
            y = -1;
            substitue = -1;
    } while (!stop);
}