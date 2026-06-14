#include "utilitaire.h"
void enregistrerDepot()
{ 
    gotoxy(30, 6);
    DEPOT d; 
    d.codeDepot = genererCodeDepot(); // genere un code unique au depot
    system("cls");
    chaine("\t\t\t Entrez le nom de l'expediteur", d.nomExpediteur, MAX_NOM);
    chaine("\t\t\t Entrez l'adresse de l'expéditeur:", d.addresseExpediteur, MAX_ADRESSE);
    chaine("\t\t\t Entrez le nom du beneficiaire:", d.nomBeneficiaire, sizeof(d.nomBeneficiaire));
    chaine("\t\t\t Entrez l'adresse du bénéficiaire:", d.adresseBeneficiaire, sizeof(d.adresseBeneficiaire));
    entier("\t\t\t Entrez le numéro de CNI:");
    d.montantDepose = reel("\t\t\t Entrez le montant à déposer");
    //d.commisions = d.montantDepose * 0.05;
    d.commisions = 0;
    printf("\t\t\t Le montant des commissions est de %.2f\n", d.commisions);
    printf("\t\t\t Le montant total à payer est de %.2f\n", d.montantDepose - d.commisions);
    recuperer_date_systeme(&d.dateDepot);
    d.dateRetrait.jours =  d.dateRetrait.mois = d.dateRetrait.annee = 0;
    d.dateAnnulation.jours = d.dateAnnulation.mois = d.dateAnnulation.annee = 0;
    d.annule = false;
    d.retire = false;   
    printf("\t\t\t Dépôt enregistré avec succès! Code de dépôt: %d\n", d.codeDepot);
    depots[nombreDepots++] = d; // ajout du depot dans le tableau et on incremente le compteur
    

} 
void afficherDepot()
{
    setlocale(LC_ALL, "fr_FR.UTF-8"); // active l'encodage français
    if(nombreDepots == 0)
    {
        printf("\t\t\t Aucun dépôt enregistré.\n");
        return;
    }
    int code = entier("\t\t\t Entrez le code de dépôt à afficher"); 
    int indice = trouverCode(code); // cherche le depot dans le tableau, retourne sa position
    if(indice == -1){     //si la fonction retourne - 1 --> depot non trouvé
        printf("\t\t\t Aucun dépot avec ce code n'a  été trouvé\n");
    }
    else{
        DEPOT d = depots[indice]; 
        printf("\t\t\t Code de dépôt: %d\n", d.codeDepot);
        printf("\t\t\t Nom de l'expéditeur: %s\n", d.nomExpediteur);
        printf("\t\t\t Adresse de l'expéditeur: %s\n", d.addresseExpediteur);
        printf("\t\t\t Nom du bénéficiaire: %s\n", d.nomBeneficiaire);
        printf("\t\t\t Adresse du bénéficiaire: %s\n", d.adresseBeneficiaire);
        printf("\t\t\t Numéro de CNI: %s\n", d.numeroCNI);
        printf("\t\t\t Montant déposé: %.2f\n", d.montantDepose);
        printf("\t\t\t Commissions: %.2f\n", d.commisions);
        printf("\t\t\t Date du dépôt: %02d/%02d/%04d\n", d.dateDepot.jours, d.dateDepot.mois, d.dateDepot.annee);
        if((!d.retire) && (!d.annule)){
            printf("\t\t\t Status : En attente\n");
        }
        if(d.retire){
            
            printf("\t\t\t Date du retrait_: %02d/%02d/%04d\n", d.dateRetrait.jours, d.dateRetrait.mois, d.dateRetrait.annee);
            printf("\t\t\t Montant retiré: %.2f\n", d.montantRetire);
            printf("\t\t\t status : Retiré\n");
        }
        if(d.annule){
            printf("\t\t\t Date de l'annulation: %02d/%02d/%04d\n", d.dateAnnulation.jours, d.dateAnnulation.mois, d.dateAnnulation.annee);
            printf("\t\t\t status : Annulé\n");
        }

    }
     
}
void retirerDepot()
{
    if(nombreDepots == 0)
    {
        printf("\t\t\t Aucun dépot enregistré.\n");
        return;
    }
    int code = entier("\t\t\t Entrez le code de dépôt à afficher");
    int indice = trouverCode(code);
    if(indice == -1){
        printf("\t\t\t Aucun dépot avec ce code n'a  été trouvé\n");
    }
    if(depots[indice].retire){
        printf("\t\t\t Ce dépôt a déjà été retiré.\n");
        printf("\t\t\t Date du retrait: %02d/%02d/%04d\n", depots[indice].dateRetrait.jours, depots[indice].dateRetrait.mois, depots[indice].dateRetrait.annee);
        return;
    }
    if(depots[indice].annule){
        printf("\t\t\t Ce dépôt a été annulé et ne peut pas être retiré.\n");
        printf("\t\t\t Date de l'annulation: %02d/%02d/%04d\n", depots[indice].dateAnnulation.jours, depots[indice].dateAnnulation.mois, depots[indice].dateAnnulation.annee);
        return;
    }
    depots[indice].retire = true;
    depots[indice].montantRetire = depots[indice].montantDepose - depots[indice].commisions;
    printf("\t\t\t retrait effectué avec succès. Montant versé: %.2f\n", depots[indice].montantDepose - depots[indice].commisions);
    recuperer_date_systeme(&depots[indice].dateRetrait);
    depots[indice].dateAnnulation.jours = depots[indice].dateAnnulation.mois = depots[indice].dateAnnulation.annee = 0;
    

}
 void enregistrerCommissions()
{
     if(nombreDepots == 0)
     {
         printf("\t\t\t Aucun dépôt enregistré.\n");
         return;
     }
     int code = entier("\t\t\t Entrez le code de dépôt pour enregistrer les commissions");
     int indice = trouverCode(code);
     if(indice == -1){
         printf("\t\t\t Aucun dépot avec ce code n'a  été trouvé\n");
     }
     else{
         if(depots[indice].annule)
         {
            printf("\t\t\t Ce depot est annule.\n");
            return;
         }
         if(depots[indice].retire)
         {
            printf("\t\t\t Ce depot a deja ete retire.\n");
            return;
         }
        if (depots[indice].commisions != 0)
        {
            printf("\t\t\t Une commission a déjà été enregistrée pour ce depot.\n");
            return;
        }
     }
     depots[indice].commisions = reel("\t\t\t Entrez le montant de la commission");
     printf("\t\t\t Commission enregistre avec succes!\n");
     printf("\t\t\t Montant depose : %.2f\n", depots[indice].montantDepose);
     printf("\t\t\t Commission: %.2f\n", depots[indice].commisions);
     printf("\t\t\t Montant Payable: %.2f\n", depots[indice].montantDepose - depots[indice].commisions);
}
void annulerDepot()
{
    if(nombreDepots == 0)
    {
        printf("\t\t\t Aucun dépot enregistré.\n");
        return;
    }
    int code = entier("\t\t\t Entrez le code de dépôt à afficher");
    int indice = trouverCode(code);
    if(indice == -1){
        printf("\t\t\t Aucun dépot avec ce code n'a  été trouvé\n");
    }
    if(depots[indice].retire)
    {
        printf("\t\t\t Ce dépôt a déjà été retiré.\n");
        printf("\t\t\t Date du retrait: %02d/%02d/%04d\n", depots[indice].dateRetrait.jours, depots[indice].dateRetrait.mois, depots[indice].dateRetrait.annee);
        return;
    }
    if(depots[indice].annule)
    {
        printf("\t\t\t Ce dépôt a été annulé et ne peut pas être retiré.\n");
        printf("\t\t\t Date de l'annulation: %02d/%02d/%04d\n", depots[indice].dateAnnulation.jours, depots[indice].dateAnnulation.mois, depots[indice].dateAnnulation.annee);
        return;
    }
    depots[indice].annule = true;
    printf("\t\t\t Dépot annulé avec succès. Montant versé: %.2f\n", depots[indice].montantDepose);
    recuperer_date_systeme(&depots[indice].dateAnnulation);
    depots[indice].dateAnnulation.jours = depots[indice].dateAnnulation.mois = depots[indice].dateAnnulation.annee = 0;
    

}
void modifierDepot()
{
   if(nombreDepots == 0)
    {
        printf("\t\t\t Aucun dépot enregistré.\n");
        return;
    }
    int code = entier("\t\t\t Entrez le code de dépôt à afficher");
    int indice = trouverCode(code);
    if(indice == -1)
    {
        printf("\t\t\t Aucun dépot avec ce code n'a  été trouvé\n");
    }
    if(depots[indice].retire)
    {
        printf("\t\t\t Ce dépôt a déjà été retiré.\n");
        printf("\t\t\t Date du retrait: %02d/%02d/%04d\n", depots[indice].dateRetrait.jours, depots[indice].dateRetrait.mois, depots[indice].dateRetrait.annee);
        return;
    }
    if(depots[indice].annule)
    {
        printf("\t\t\t Ce dépôt a été annulé et ne peut pas être modifié.\n");
        printf("\t\t\t Date de l'annulation: %02d/%02d/%04d\n", depots[indice].dateAnnulation.jours, depots[indice].dateAnnulation.mois, depots[indice].dateAnnulation.annee);
        return;
    }

    afficherDepot();
    chaine( "\t\t\t Nouveau nom expediteur", depots[indice].nomExpediteur, MAX_NOM);
    chaine( "\t\t\t Nouvelle adresse expediteur", depots[indice].addresseExpediteur, MAX_ADRESSE); 
    chaine("\t\t\t Nouveau nom Beneficiaire", depots[indice].nomBeneficiaire, sizeof(depots[indice].nomBeneficiaire));
    chaine("\t\t\t Nouvelle adresse Beneficiaire", depots[indice].adresseBeneficiaire, sizeof(depots[indice].adresseBeneficiaire)); 
    entier("\t\t\t Nouveau numéro CNI");
    depots[indice].montantDepose = reel("\t\t\t Nouveau montant déposé");
    printf("\t\t\t Dépot modifier avec succès!\n");
    
}
void supprimerDepot()
{
    if(nombreDepots == 0)
    {
        printf("\t\t\t Aucun dépot enregistré.\n");
        return;
    }
    int code = entier("\t\t\t Entrez le code de dépôt à afficher");
    int indice = trouverCode(code);
    if(indice == -1){
        printf("\t\t\t Aucun dépot avec ce code n'a  été trouvé\n");
        return;
    }
    for ( int i = indice; i < nombreDepots - 1; i++)
    {
        depots[i] = depots[i + 1];
    }
    nombreDepots--;
    printf("\t\t\t Depot supprimé avec succès!\n");
}
void situationDepots()
{
    if(nombreDepots == 0)
    {
        printf("\t\t\t Aucun dépot enregitré.\n");
        return;
    }
    double *montantTotal = calloc (1, sizeof(int));
    for ( int i = 0; i < nombreDepots; i++)
    {
        *montantTotal += depots[i].montantDepose;
    }
    printf("\t\t\t Nombre de dépôts:%d\n", nombreDepots);
    printf("\t\t\t MOntant total des dépots:%.2f", *montantTotal);
}
void situationRetraits()
{
    int *nombreRetraits = calloc ( 1 , sizeof(int));
    double *montantTotal = calloc(1, sizeof(double));
    for ( int i = 0; i < nombreDepots; i++)
    {
        if(depots[i].retire == true)
        {
            (*nombreRetraits)++;
            *montantTotal += depots[i].montantRetire;
        }
    }
    printf("\t\t\t Nombre de retraits: %d\n", *nombreRetraits);
    printf("\t\t\t Montant total des retraits : %.2f\n", *montantTotal);
}
void situationCommisions()
{
    // Declaration du compteur de commissions
    int *nombreCommisions = calloc(1, sizeof(int));
    // Declaration du montant total des commisions
    double *montantTotal = calloc (1, sizeof(double));
    // Parcourir tous les dépôts
    for ( int i = 0; i < nombreDepots; i++)
    {
        // Vérifier si le dépot a une commision enregistrée
        if (depots[i].commisions > 0)
        {
            // incrementer le compteur de commissions
            (*nombreCommisions)++;
            // Ajouter la commission au montant total
            *montantTotal += depots[i].commisions;
        }
    }
    printf("\t\t\t Nombre de commissions: %d\n", *nombreCommisions);
    printf("\t\t\t Montant total des commissions: %.2f\n", *montantTotal);
}
void listeDepotsParDate()
{
    Date date = saisirDate();
    // Affichage de l'entête avec la date saisie
    printf("\t\t\t Dépôts du %02d/%02d/%04d:\n", date.jours, date.mois, date.annee);
    // Parcourir tous les dépôts
    for ( int i = 0; i < nombreDepots; i++)
    {
        if(depots[i].dateDepot.jours == date.jours && depots[i].dateDepot.mois == date.mois && depots[i].dateDepot.annee == date.annee)
        {
            DEPOT d = depots[i]; // Récupère le dépot correspondant
            printf("\t\t\t Code de dépôt: %d\n", d.codeDepot);
            printf("\t\t\t Nom de l'expéditeur: %s\n", d.nomExpediteur);
            printf("\t\t\t Adresse de l'expéditeur: %s\n", d.addresseExpediteur);
            printf("\t\t\t Nom du bénéficiaire: %s\n", d.nomBeneficiaire);
            printf("\t\t\t Adresse du bénéficiaire: %s\n", d.adresseBeneficiaire);
            printf("\t\t\t Numéro de CNI: %s\n", d.numeroCNI);
            printf("\t\t\t Montant déposé: %.2f\n", d.montantDepose);
            printf("\t\t\t Commissions: %.2f\n", d.commisions);
            printf("\t\t\t Date du dépôt: %02d/%02d/%04d\n", d.dateDepot.jours, d.dateDepot.mois, d.dateDepot.annee);
        }
    }

}




