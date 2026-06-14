#include "utilitaire.h"
#define MAX_SIZE 50
#define MAX_TENTATIVES 3
#define MAX_DEPOT 500
#define MAX_NOM 70
#define MAX_ADRESSE 150
#define MAX_CNI 30
typedef struct {
    int jours, mois, annee;
} Date;
typedef struct {
    int codeDepot;
    char nomExpediteur[MAX_NOM];
    char addresseExpediteur[MAX_ADRESSE];
    char nomBeneficiaire[MAX_NOM];
    char adresseBeneficiaire[MAX_ADRESSE];
    char numeroCNI[MAX_CNI];
    Date dateDepot;
    Date dateRetrait;
    Date dateAnnulation;
    double montantDepose;
    double montantRetire;
    double commisions;
    bool annule;
    bool retire;
} DEPOT;
extern DEPOT depots[MAX_DEPOT];
extern int nombreDepots;

