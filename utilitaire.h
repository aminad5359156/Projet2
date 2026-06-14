#ifndef __UTILITAIRE_H__
#define __UTILITAIRE_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include <locale.h>
#include <conio.h>
#include <stdbool.h>
#include "depot.h"

void gotoxy(int , int );
void montextedeconnexion (int, int ,char*);
void pagedeconnexion ();
int identifierUtilisateur();
void saisieSecurisee( char *dest, const char *label);
void viderBuffer();
void saisieMasque(char *dest, const char *label);
void viderBuffer();
void chaine(char *, char *, int );
int  entier(char *);
float  reel(char *);
void afficherMenu();
void enregistrerDepot();
void afficherDepot();
void retirerDepot();
void recuperer_date_systeme(Date * );
int genererCodeDepot();
int trouverCode(int );
void enregistrerCommissions();
void annulerDepot();
void modifierDepot();
void supprimerDepot();
void situationDepots();
void situationRetraits();
void situationCommisions();
int dateValide(Date);
Date saisirDate();
void listeDepotsParDate();
void setcolor(int, int);
#endif