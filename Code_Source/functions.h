#ifndef FONCTIONS_H
#define FONCTIONS_H

typedef struct elementCarte {
    int num;
    char type;
    struct elementCarte *next;
} ElementCarte;

extern ElementCarte *Carte_Paquet;
extern ElementCarte *Zone1[8];
extern ElementCarte *Zone2[4];
extern ElementCarte *Zone3[4];
extern int totalZone3[4];

void initialisation(void);
void InsertCarte(int pos, int num, char type);
void CreatePaquet(void);
void ManipulerZone1(void);
void Zone1_vers_Zone3(void);
void Zone1_vers_Zone2(void);
void Zone1_vers_Zone1(void);
void Zone2_vers_Zone1(void);
void Zone2_vers_Zone3(void);
void ResetGame(void);
void Display(void);
int isWinner(void);

#endif
