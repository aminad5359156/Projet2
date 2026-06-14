#include "utilitaire.h"
void gotoxy(int x, int y) 
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void montextedeconnexion (int X, int Y ,char* texte)
{
    gotoxy(X, Y);
    int limite = 1;
    for(int i = 0; i < limite; i++)
    {
        if(texte[i] != '\0')
        {
            limite++;
        }

        printf("%c", texte[i]);
         Sleep(200);
    }


}
void pagedeconnexion()
{
    setlocale(LC_ALL, "fr_FR.UTF-8");
    system("cls");
    setcolor(14, 0);
    montextedeconnexion(30, 3, "===================================");
    setcolor(11, 0);
    montextedeconnexion(30, 5, "Bienvenue dans le projet de gestion");
    setcolor(11, 0);
    montextedeconnexion(30, 6, " de transfert d'argent et suivi des");
    montextedeconnexion(30, 7, "Commissions.");
    setcolor(10, 0);
    montextedeconnexion(30, 8, "Ce projet a été réalisé par:");
    setcolor(15, 0);
    montextedeconnexion(30, 9, "Aminatou Diallo");
    montextedeconnexion(30, 10, "Oumar Tounkara");
    montextedeconnexion(30, 11, "Hadja Ramatoulaye Diallo");
    montextedeconnexion(30, 12, "Mamadou Aliou Sow");
    montextedeconnexion(30, 13, "Ousmane Touré.");
    montextedeconnexion(30, 14, "**********************************");
    setcolor(15, 0);
    Sleep(20);
    system("cls");
}
void saisieSecurisee( char *dest, const char *label)
{
    char buffer[MAX_SIZE];
    int valide = 0;
    while (!valide)
    {
        A:printf("%s:", label);
        if (fgets(buffer, sizeof(buffer), stdin))
        {
            if (strchr(buffer, '\n') == NULL)
            {
            printf("\t\t\t Erreur: saisie trop long longue! Arretez de tricher.\n");
            viderBuffer();
            //continue;
            goto A;
            }
        }
        buffer[strcspn(buffer, "\n")] = 0;
        if (strlen(buffer) == 0)
        {
            printf("\t\t\t Erreur: la saisie est vide!\n");
            goto A;
        }
        else if (strchr(buffer, ' ') != NULL)
        {
            printf("\t\t\t Erreur: pas d'espace autorise!\n");
            goto A;
        }
        else {
            strcpy (dest, buffer);
            valide = 1;
        }
        
    }
    bool contient_lettre = false;
    for(int i = 0; buffer[i] != '\0'; i++)
    {
        if(!isdigit((unsigned char)buffer[i]))
        {
            contient_lettre = true;
            break;
        }
        }
        if(!contient_lettre)
        {
            printf("\t\t\t Erreur: la saisie ne peut pas contenir que des chiffres.\n");
            goto A;
            //continue;
        }
        else {
            strcpy (dest, buffer);
            valide = 1;
        }
        
}
void saisieMasque(char *dest, const char *label)
{
    int i = 0;
    char ch;
    printf("%s", label);
    while ( i < MAX_SIZE - 1)
    {
        ch = getch();
        if ( ch == 13)
        {
            break;
        }
        else if(ch == 8)
        {
            if( i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            dest[i++] = ch;
            printf("*");
        }
    }
    dest[i] = '\0';
    printf("\n");
}
int identifierUtilisateur()
{
    char userSaisie[MAX_SIZE];
    char passSaisie[MAX_SIZE];
    int essais = 0;
    while (essais < MAX_TENTATIVES)
    {   
       printf("\t\t\t Tentative %d/%d\n", essais + 1, MAX_TENTATIVES);
       saisieSecurisee(userSaisie, "\t\t\t NomUtilisateur");
       saisieMasque(passSaisie, "\t\t\t Mot de passe");
        if (strcmp(userSaisie, "Aminatou") == 0 && (strcmp(passSaisie, "1234") == 0))
        {
            return 1;
        }
        essais++;
        printf("\t\t\t Identifiant faux!\n");

    }
    printf("\t\t\t tentative d'intrusion detecte. System lourdement verrouillee.\n");
    return 0;
    Sleep(1500);
}
void setcolor(int couleurTexte, int couleur)
{
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hconsole, couleurTexte);

}

void viderBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void chaine(char *message, char *dest, int taille)
{
    char temp[256];
    int valide = 0;

while(!valide)
    {
        printf("%s :",message);
        if(fgets(temp,sizeof(temp),stdin) == NULL){
            clearerr(stdin);
            printf("\t\t\t Saisie interrompue par l'utilisateur.\n");
            continue;
        }
        temp[strcspn(temp, "\n")] = '\0';
        if(strlen(temp) == sizeof(temp) - 1 && !feof(stdin))
        {
            viderBuffer();
            printf("\t\t\t saisie trop longue veuillez reessayer.\n");
            continue;
        }
        int space = 1, i ;
        for(i = 0; temp[i] != '\0'; i++){
            if(!isspace((unsigned char)temp[i])){ space = 0; break; 
            }
        }
        if(space){
            printf("\t\t\t La saisie ne peut pas être que des espaces. Veuillez réessayer.\n");
            continue;
        }
        bool contient_lettre = false;
        for(i = 0; temp[i] != '\0'; i++){
            if(!isdigit((unsigned char)temp[i]))
            {
                contient_lettre = true;
                break;
            }
        }
            if(!contient_lettre)
            {
                printf("\t\t\t Erreur: la saisie ne peut pas contenir que des chiffres.\n");
                continue;
            }
        strncpy(dest,temp, taille - 1);
        dest[taille - 1] = '\0';
        valide = 1;
    }
}

int entier(char *message)
{
    char temporaire[250];
    int valeur, valide = 0;
    while(!valide){
        printf("%s :",message);
        if(fgets(temporaire, sizeof(temporaire), stdin) == NULL){
            clearerr(stdin);
            printf("\t\t\t Saisie interrompue par l'utilisateur.\n");
            continue;
        }
        temporaire[strcspn(temporaire, "\n")] = '\0';
        char *fin;
        valeur = (int)strtol(temporaire, &fin, 10);
        if (fin == temporaire || *fin != '\0'){
            printf("\t\t\t Saisie invalide. Veuillez entrer un nombre entier.\n");
            continue;
        }
        valide = 1;
    }
    return valeur;
 }
 float  reel(char *message){
    char temporaire[250];
    float valeur;
    int valide = 0;
    while(!valide){
        printf("%s :", message);
        if(fgets(temporaire, sizeof(temporaire), stdin) == NULL){
            
            clearerr(stdin);
            printf("\t\t\t Saisie interrompue! Veuillez réessayer.\n");
            continue;
        }
        temporaire[strcspn(temporaire, "\n")] = '\0' ;
        char *fin;
        valeur = (float)strtod(temporaire, &fin);
        if(fin == temporaire || *fin != '\0'){
            printf("\t\t\t Saisie non valide! Veuillez entrer un nomnre réel.\n");
            continue;
        }
        if(valeur <= 0){
            printf("\t\t\t Veuillez entrez une somme superieure à zéro.\n");
            continue;
        }
        valide = 1;
    } 
    return valeur;
 }
void recuperer_date_systeme(Date *d)
{
    time_t maintenant = time(NULL);
    struct tm *tempsReel = gmtime(&maintenant);
    d->jours = tempsReel->tm_mday;
    d->mois = tempsReel->tm_mon + 1;
    d->annee = tempsReel->tm_year + 1900;
}
int genererCodeDepot(void){
    int min = 2007;
    int i;
    for(i = 0; i < nombreDepots; i++){
        if (depots[i].codeDepot >= min){
            min = depots[i].codeDepot + 1;
        }
    }
    return min;
}
int trouverCode(int code)
{
    int i;
    for(i = 0; i < nombreDepots; i++){
        if(depots[i].codeDepot == code){
            return i;
        }
    }
    return -1;
}
int dateValide(Date date)
{
    // Verifier le mois
    if(date.mois < 1 || date.mois > 12)
    {
        return 0;
    }
    // Verifier l'annee
    if(date.annee < 1900)
    {
        return 0;
    }
    // Tableau des jours par mois
    int joursParMois[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    //Verifier si l'annee est bissextile
    if ( date.annee %4 == 0)
    {
        joursParMois[1] = 29;
    }
    //Verification du jour
    if ( date.jours < 1 || date.jours > joursParMois[date.mois - 1])
    {
        return 0;
    }
    return 1;
}
Date saisirDate()
{
    Date date;
    do
    {
        date.jours = entier("\t\t\t Entrer le jour:");
        date.mois = entier("\t\t\t Entrer le mois:");
        date.annee = entier("\t\t\t Entrer l'annee:");
        if(!dateValide(date))
        {
            printf("Date invalide, veuillez reesayer.\n");
        }

    } while (!dateValide(date));
    return date;
}




