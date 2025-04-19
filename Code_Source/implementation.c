#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "functions.h"

ElementCarte *Carte_Paquet;
ElementCarte *Zone1[8];
ElementCarte *Zone2[4];
ElementCarte *Zone3[4];
int totalZone3[4];

// Initialisation des variables globales à utiliser
void initialisation(){
    Carte_Paquet = NULL;
    int i;
    for (i = 0; i < 8; i++) Zone1[i] = NULL;
    for(i=0;i<4;i++){
        Zone2[i] = NULL;
        Zone3[i] = NULL;
        totalZone3[i] = 0;
    }
}

// Fonction qui fait la creation et l'insertion d'une carte dans une position donnée
void InsertCarte(int pos, int num, char type){
    ElementCarte *nv_carte = (ElementCarte*)malloc(sizeof(ElementCarte));
    nv_carte->num=num;
    nv_carte->type=type;
    ElementCarte *tmp=Carte_Paquet;
    if (pos==0){
        nv_carte->next=Carte_Paquet;
        Carte_Paquet=nv_carte;
        return;
    }
    int i;
    for (i=0;i<pos-1;i++) tmp=tmp->next;
    nv_carte->next=tmp->next;
    tmp->next=nv_carte;
}

// Fonction qui fait la Creation d'un paquet de carte melangé
void CreatePaquet(){
    int i, j, pos, total=0;
    for (i = 3; i <= 6; i++) {
        for (j = 1; j <= 13; j++) {
            pos = rand()%(total+1);
            InsertCarte(pos,j,i);
            total++;
        }
    }
}

// Fonction qui fait distribuer les cartes dans la zone1
void ManipulerZone1(){
    ElementCarte *tmp1, *tmp2, *tmpCol;
    int ligne, col;
    for (ligne = 0; ligne < 7; ligne++) {
        for (col = 0; col < 8; col++) {
            if (ligne == 6 && col > 3) break;
            tmp1 = Carte_Paquet;
            tmp2 = Carte_Paquet;
            tmpCol = Zone1[col];
            while (tmp1->next != NULL) tmp1 = tmp1->next;
            if (tmp2->next != NULL) {
                while (tmp2->next != tmp1) {
                    tmp2 = tmp2->next;
                }
            }
            tmp2->next = NULL;
            if (Zone1[col] == NULL) {
                Zone1[col] = tmp1;
                tmp1->next = NULL;
            } else {
                while (tmpCol->next != NULL) {
                    tmpCol = tmpCol->next;
                }
                tmpCol->next = tmp1;
                tmp1->next = NULL;
            }
        }
    }
}

// Les fonctions de déplacement des cartes
void Zone1_vers_Zone3(){
    int source, destination;
    printf("Colonne Source n° : ");
    scanf("%d",&source);
    printf("colonne Destin n° : ");
    scanf("%d",&destination);
    ElementCarte *ColTmp1 = Zone1[source-1];
    ElementCarte *ColTmp2 = NULL;
    ElementCarte *TmpZone3 = Zone3[destination-1];
    if(TmpZone3 != NULL) {
        while (TmpZone3->next != NULL) {
            TmpZone3 = TmpZone3->next;
        }
    }
    if(ColTmp1 != NULL){
        while (ColTmp1->next != NULL){
            ColTmp2 = ColTmp1;
            ColTmp1 = ColTmp1->next;
        }
    }
    if ((ColTmp1->num) == (totalZone3[destination-1] + 1)) {
        if (ColTmp1->type == destination + 2) {
            if (Zone3[destination-1] == NULL) {
                Zone3[destination-1] = ColTmp1;
            } else {
                TmpZone3->next = ColTmp1;
            }
            if (ColTmp2 == NULL) {
                TmpZone3 = Zone1[source-1];
                Zone1[source-1] = NULL;
            } else {
                TmpZone3 = ColTmp1;
                ColTmp2->next = NULL;
            }
            totalZone3[destination-1] += 1;
        }else {
            printf("\nLa carte a deplacer doit etre du meme type des cartes de la colonne de destination!\nENTER POUR CONTINUER");
            getchar();
            getchar();
        }
    }else {
        printf("\nLe numero de la carte a deplacer doit etre superieur par 1 de la derniere carte de la colonne de destination!\nENTER POUR CONTINUER");
        getchar();
        getchar();
  }
}

void Zone1_vers_Zone2(){
    int Source, Destination;
    printf("Table Source n° : ");
    scanf("%d",&Source);
    printf("Table Destin n° : ");
    scanf("%d",&Destination);

    if (Zone2[Destination-1] == NULL) {
        if (Zone1[Source-1] != NULL) {
            ElementCarte *Tmp1 = Zone1[Source-1];
            ElementCarte *Tmp2 = NULL;
            while (Tmp1->next != NULL) {
                Tmp2 = Tmp1;
                Tmp1 = Tmp1->next;
            }
            if (Tmp2 == NULL) {
                Zone2[Destination-1] = Zone1[Source-1];
                Zone1[Source-1] = NULL;
            } else {
                Zone2[Destination-1] = Tmp1;
                Tmp2->next = NULL;
            }
        } else {
            printf("\nLa colonne source est vide. ENTER POUR CONTINUER");
            getchar();
            getchar();
        }
    } else {
        printf("\nLa colonne destination est pleinne. ENTER POUR CONTINUER");
        getchar();
        getchar();
    }
}

void Zone1_vers_Zone1(){
    int Source, Destination;
    int SourceColor=1;
    int DestinColor=1;
    printf("Table Source n° : ");
    scanf("%d",&Source);
    printf("Table Destin n° : ");
    scanf("%d",&Destination);
    if (Source < 1 || Source > 8 || Source < 1 || Source>8) {
        printf("\nLes numeros de colonne et de ZONE doivent etre dans les plages valides.\n");
        getchar();
        getchar();
        return;
    }
    ElementCarte *pt1=NULL;
    ElementCarte *pt2=NULL;
    ElementCarte *tmpcol1=Zone1[Source-1];
    ElementCarte *tmpcol2=Zone1[Destination-1];


    while(tmpcol1->next!=NULL){
        pt1=tmpcol1;
        tmpcol1=tmpcol1->next;
    }

    while(tmpcol2->next!=NULL){
        pt2=tmpcol2;
        tmpcol2=tmpcol2->next;
    }
    if (tmpcol1->type == 3 || tmpcol1->type == 4)
        SourceColor=1;
    else
        SourceColor=0;

    if (tmpcol2->type == 3 || tmpcol2->type == 4)
        DestinColor=1;
    else
        DestinColor=0;
    if (pt2==NULL){
        tmpcol1->next=NULL;
        tmpcol2=tmpcol1;

    }else{
        if(tmpcol2->num==(tmpcol1->num)+1 &&  SourceColor!=DestinColor ){
            tmpcol2->next=tmpcol1;
            tmpcol1->next=NULL;
            pt1->next=NULL;
        }else{
            printf("\nIl faut soit un numero inferieur OU un couleur different de celle de la colonne de destination!\nENTRER POUR CONTINUER");
            getchar();
            getchar();

        }
    }
}

void Zone2_vers_Zone1(){
    int Source, Destination;
    printf("Table Source n° : ");
    scanf("%d",&Source);
    printf("Table Destin n° : ");
    scanf("%d",&Destination);
    int SourceColor=1;
    int DestinColor=1;
    ElementCarte *Tmp = Zone1[Destination-1];

    if (Zone2[Source-1] != NULL) {
        if (Zone1[Destination-1] == NULL) {
            Zone1[Destination-1] = Zone2[Source-1];
            Zone2[Source-1] = NULL;
        } else {
            while (Tmp->next != NULL) {
                Tmp = Tmp->next;
            }
            if ((Tmp->type == 3) || (Tmp->type == 4))
                DestinColor = 1;
            else
                DestinColor = 0;
            if ((Zone2[Source-1]->type == 3) || (Zone2[Source-1]->type == 4))
                SourceColor = 1;
            else
                SourceColor = 0;

            if ((SourceColor != DestinColor)) {
                if ((Zone2[Source-1]->num == (Tmp->num) - 1)) {
                    Tmp->next = Zone2[Source-1];
                    Zone2[Source-1] = NULL;
                }else {
                    printf("\nLe numero de la carte a deplacer doit etre inferieur par 1 de la derniere carte de la pile de destination!\nENTER POUR CONTINUER");
                    getchar();
                    getchar();
                }
            }else {
                printf("\nLes couleurs doivent etre differentes!\nENTRER POUR CONTINUER");
                getchar();
                getchar();
            }
        }
    }else {
        printf("\nColonne temporaire vide!\nENTRER POUR CONTINUER");
        getchar();
        getchar();
    }
}

void Zone2_vers_Zone3(){
    int Source, Destination;
    printf("Table Source n° : ");
    scanf("%d",&Source);
    printf("Table Destin n° : ");
    scanf("%d",&Destination);
    if (Zone2[Source-1] != NULL) {
        ElementCarte *tmpZone2 = Zone2[Source-1];
        ElementCarte *tmpZone3 = Zone3[Destination-1];

        if (tmpZone3 != NULL) {
            while (tmpZone3->next != NULL) {
                tmpZone3 = tmpZone3->next;
            }
        }
        if ((tmpZone2->num) == (totalZone3[Destination-1] + 1)) {
            if (tmpZone2->type == Destination + 2) {

                if (Zone3[Destination-1] == NULL) {
                    Zone3[Destination-1] = tmpZone2;
                } else {
                    tmpZone3->next = tmpZone2;
                    tmpZone2->next = NULL;
                }
                Zone2[Source-1] = NULL;
                totalZone3[Destination-1] += 1;
            }else {
                printf("\nLa carte a deplacer doit etre du meme type de la pile de destination!\nENTER POUR CONTINUER");
                getchar();
                getchar();
            }
        }else {
            printf("\nLe numero de la carte a deplacer doit etre superieur par 1 de la derniere carte de la pile de destination!\nENTER POUR CONTINUER");
            getchar();
            getchar();
        }
    } else {
        printf("\nLa colonne source de la Zone2 est vide.\nENTER POUR CONTINUER");
        getchar();
        getchar();
    }
}

// Fonction qui libère les espaces mémoires allouées
void ResetGame(){
    int i;
    for (i = 0; i < 4; i++) {
        free(Zone2[i]);
    }
    ElementCarte *pt;
    for (i = 0; i < 4; i++) {
        pt = Zone3[i];
        if(pt==NULL) return;
        while (pt->next != NULL) {
            pt = Zone3[i];
            Zone3[i] = Zone3[i]->next;
            free(pt);
        }
        free(Zone3[i]);
    }
    for (i = 0; i < 8; i++) {
        pt = Zone1[i];
        if(pt==NULL) return;
        while (pt->next != NULL) {
            pt = Zone1[i];
            Zone1[i] = Zone1[i]->next;
            free(pt);
        }
        free(Zone1[i]);
    }
}

// Fonction qui fait l'affichage
void Display(){
    printf("\n===========> Vous devez donner attention au numero de chaque champs! <===========\n");
    char c = 'a';
    printf("\n**************************** Zone2 (Zone FreeCell) ******************************\n\n");
    int i;
    for (i = 0; i < 4; i++) {
        printf("%d:", i + 1);
        if (Zone2[i] == NULL) {
            printf("[    ]     ");
        } else {
            if (Zone2[i]->num == 1)  c = 'A';
                if (Zone2[i]->num == 11) c = 'J';
            if (Zone2[i]->num == 12) c = 'Q';
          if (Zone2[i]->num == 13) c = 'K';
          if (c == 'a')  printf("[%02d/%c]    ", Zone2[i]->num, Zone2[i]->type);
          else  printf("[%c /%c]     ", c, Zone2[i]->type);
          c = 'a';
          printf(" ");
        }
      }
      printf("\n");

      printf("\n**************************** Zone3 (Zone de fondation) **************************\n");
      ElementCarte *TmpZone3;
      for (i = 0; i < 4; i++) {
        TmpZone3 = Zone3[i];
        if (TmpZone3 == NULL) {
          printf("\n%d-%c:[    ]  ", i + 1, i + 3);
        } else {
          printf("\n%d-%c:" , i + 1, i + 3);
          while (TmpZone3 != NULL) {
            if (TmpZone3->num == 1)  c = 'A';
            if (TmpZone3->num == 11) c = 'J';
            if (TmpZone3->num == 12) c = 'Q';
            if (TmpZone3->num == 13) c = 'K';
            if (c == 'a')  printf("[%02d/%c]", TmpZone3->num, TmpZone3->type);
            else  printf("[%c /%c]", c, TmpZone3->type);
            c = 'a';
            printf(" ");
            TmpZone3 = TmpZone3->next;
          }
        }
        printf(" ");
      }
      printf("\n");

      printf("\n**************************** Zone1 (Plateau de jeu) *****************************\n\n");
      ElementCarte *TmpZone1;
      for (i = 0; i < 8; i++) {
        TmpZone1 = Zone1[i];
        if (TmpZone1 == NULL) {
          printf("Colonne %d: [    ]", i + 1);
        } else {
          printf("Colonne %d: ", i + 1);
          while (TmpZone1 != NULL) {
            if (TmpZone1->num == 1)  c = 'A';
            if (TmpZone1->num == 11) c = 'J';
            if (TmpZone1->num == 12) c = 'Q';
            if (TmpZone1->num == 13) c = 'K';
            if (c == 'a')  printf("[%02d/%c]", TmpZone1->num, TmpZone1->type);
            else  printf("[%c /%c]", c, TmpZone1->type);
            c = 'a';
            printf(" ");
            TmpZone1 = TmpZone1->next;
          }
        }
        printf("\n");
      }
      printf("\n");
}

// Fonction qui teste si le joueur a gangné la partie
int isWinner(){
    int v = 1;
    ElementCarte *pt;
    int i;
    for (i = 0; i < 4; i++) {
        pt = Zone3[i];
        if (pt != NULL) {
            while (pt->next != NULL) {
                pt = pt->next;
            }
            if (pt->num != 13) v = 0;
            else v = 1;
        }
    }
    if (v!=0) {
        system("cls");
        printf("*************************************************************\n");
        printf("*                                                           *\n");
        printf("*                                                           *\n");
        printf("*                                                           *\n");
        printf("*                    WINNER WINNER WINNER                   *\n");
        printf("*                                                           *\n");
        printf("*                                                           *\n");
        printf("*                                                           *\n");
        printf("*************************************************************\n");
        ResetGame();
        return 1;
    }
    else return 0;
}


