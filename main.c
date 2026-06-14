#include "utilitaire.h"
int main() {
    setlocale(LC_ALL, "fr_FR.UTF-8");
    pagedeconnexion();
    if (identifierUtilisateur())
    {
        printf("\t\t\t ---ACCES AU MENU GENERAL ACCORDE---");
        Sleep(2000);
    }
    else
    {
        return 0;
    }
menu:
    afficherMenu();
    int choix;
    gotoxy(30,17);
   choix = entier("\t\t\t Entrez votre choix");
     switch(choix){
        case 1:{

            enregistrerDepot();
            Sleep(5000);
            goto menu;
        }
        case 2:{
            afficherDepot();
            Sleep(5000);
            goto menu;
        }
        case 3:{
            retirerDepot();
            Sleep(5000);
            goto menu;
        }
        case 4:{
            enregistrerCommissions();
            Sleep(5000);
            goto menu;
        }
        case 5:
        {
            annulerDepot();
            Sleep(5000);
            goto menu;
        }
        case 6:
        {
            modifierDepot();
            Sleep(5000);
            goto menu;
        }
        case 7:
        {
            supprimerDepot();
            Sleep(5000);
            goto menu;
        }
        case 8:
        {
            situationDepots();
            Sleep(5000);
            goto menu;
        }
        case 9:
        {
            situationRetraits();
            Sleep(5000);
            goto menu;
        }
        case 10:
        {
            situationCommisions();
            Sleep(5000);
            goto menu;
        }
        case 11:
        {
            listeDepotsParDate();
            Sleep(5000);
            goto menu;
        }
        case 0:
        {
            exit(0);
        }
        default:{
            printf("Choix invalide. Veuillez entrer un nombre entre 1 et 19.\n");
             Sleep(2000);
             goto menu;
        }
    }
    return 0;
}