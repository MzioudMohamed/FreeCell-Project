#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "functions.h"

int main() {
    system("color F2");
    int mouvement = -1;
    srand(time(NULL));
    CreatePaquet();
    ManipulerZone1();
    while (mouvement != 0) {
        Display();
        printf("0 - Quitter\n");
        printf("1 - Zone1 to Zone3\n");
        printf("2 - Zone1 to Zone2\n");
        printf("3 - Zone1 to Zone1\n");
        printf("4 - Zone2 to Zone1\n");
        printf("5 - Zone2 to Zone3\n");
        printf("\nTaper le numero de votre mouvement : ");
        scanf("%d", &mouvement);
        getchar();
        switch (mouvement) {
            case 0:
                system("cls");
                ResetGame();
                return 0;
                break;
            case 1: Zone1_vers_Zone3(); break;
            case 2: Zone1_vers_Zone2(); break;
            case 3: Zone1_vers_Zone1(); break;
            case 4: Zone2_vers_Zone1(); break;
            case 5: Zone2_vers_Zone3(); break;
            default:
                printf("\nEnter un numero entre 0 et 5\n");
                getchar();
                break;
        }
    }
    return 0;
}
