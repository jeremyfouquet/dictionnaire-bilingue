/*******************************************************
# Nom ......... : dictionnaire
# Rôle ........ : Dictionnaire Japonais-Francais
# Auteur ...... : jeremy fouquet
# Version ..... : V1 du 12/05/2022
# Licence ..... : réalisé dans le cadre du cours de Gilles Bernard pour la licence 2 Informatique de L'IED Paris 8
# Compilation : g++ *.cpp -o dictionnaire -Wall -lX11 -lXm -lXt
# Usage : ./dictionnaire
********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_MAX 1000 // Tableau de taille 1000 (pour les lignes)
#define MOT_MAX 100 // Tableau de taille 100 (pour les mots)
#define string char *

#define cdr(x) (x)->cdr
#define form(x) (x)->form // trouver la forme à traduire
#define traductions(x) (x)->traductions // trouver la première traduction


// Constantes
const char separateur = '/';
const char crochet1 = '[';
const char crochet2 = ']';
const char parenthese1 = '(';
const char parenthese2 = ')';
const char d[] = " ";

// variables
char * pointeur;
string nomDico = "dico.utf"; // nom du fichier


typedef struct {string form ; string secondform ; int id ;} japonais ; // partie japonaise du dictionnaire
typedef struct Translate {string form ; int id ; struct Translate * cdr ;} Translate, * francais ; // partie française du dictionnaire
typedef struct Entry {japonais form ; francais traductions ; struct Entry * cdr ;} Entry, * dictionnaire ; // entree du dictionnaire
dictionnaire japonais_français = NULL ; // dictionnaire

// PROTOTYPE de fonction de base
void usage(const string, const string); // En cas d'erreur
dictionnaire pushTraduction(japonais form, francais traductions, dictionnaire nouvelEntree); // Ajout une entree au dictionnaire
void lecturedictionnaire(string); // lis le fichier et traduit la lecture en structure pour remplir le dictionnaire japonais_françaisre
francais pushFrancais(string, int, francais); // Ajout une entree à la liste chainée francais, pour la traduction du dictionnaire
int my_strcmp(const string, const string); // compare 2 chaine entre elle => 0 si egale
japonais recupereJaponais(string, int); // Traduit la ligne renvoyé par le fichier en structure japonais pour le dictionaire -> form
francais recupereFrancais(string, int); // Traduit la ligne renvoyé par le fichier en liste chainé de structure français pour le dictionaire -> traductions
int recupereIdentifiant(string); // Traduit la ligne renvoyé par le fichier en identifiant -> form.id ; -> traductions.id
string supprimerCategorie(string); // Filtre la partie entre parenthese qui suit directement le separateur de la chaine de caractere passé en paramettre
int estVide(void * liste); // protege une structure vide
char * ajoutCrochet(const char *); // concatene des crochets autoure d'une chaine de caractere ex [ma chaine]
string strstr(const string Source, const string) ; // trouve une chaine de char dans une autre (Source)


// PROTOTYPE des fonctions d’accès élémentaires :
dictionnaire rechercheJaponais(string); // cherche le cdr correspondant au mot passé en parametre via traductions(cdr)
dictionnaire rechercheTraduction(string); // cherche le cdr correspondant au mot passé en parametre via form(cdr)
dictionnaire rechercheIdentifiant(int identifiant); // cherche le cdr correspondant à l'id passé en parametre via form(cdr) ou traduction(cdr)
void accesFrancais(dictionnaire); // parcours cdr et affiche form(cdr);
void accesJaponais(dictionnaire); // affiche form(dictionnaire).form et form(dictionnaire).secondform


// PROTOTYPE des fonctions d'echange avec l'utilisateur :
void traduire (string); // choix n° 1 japonais-français
void rechercheMot(string motFr); // choix n° 2 français-japonais
void rechercheId(int identifiant); // choix n° 3 recherche par identifiant
void selection(void); // interface rudimentaire
void choix(int); // interface rudimentaire


int main(int argc, const char * argv[]) {
    string nomFichier = nomDico;
    lecturedictionnaire(nomFichier);
    selection();
    return 0;
}

void selection() {
    printf("%s\n", "1 : japonais -> français");
    printf("%s\n", "2 : français -> japonais");
    printf("%s\n", "3 : recherche par identifiant");
    printf("%s\n", "0 : STOP");
    printf("%s\n", "quel est votre choix ?");
    char select;
    scanf(" %c", &select);    // Entrer : magnitude
    choix(select);
}

void choix(int select) {
    switch(select) {
        case '1' :
            printf("%s\n", "Ecrire un mot en Japonais :");
            char motAtraduire[MOT_MAX];
            scanf("%s", motAtraduire);
            traduire(motAtraduire);
            break;
        case '2' :
            printf("%s\n", "Ecrire un mot ou une phrase en Français :");
            char motsARechercher[MOT_MAX];
            scanf(" %[^\n]",motsARechercher);
            rechercheMot(motsARechercher);
            break;
        case '3' :
            printf("%s\n", "Ecrire un identifiant à 7 chiffre commençant par 1 ex '1010200' :");
            int id;
            scanf("%d", &id);
            rechercheId(id);
            break;
        case '0' :
            puts("Au revoir !");
            exit(0) ;
        default :
            puts("Erreur de choix ! veuillez selectionnez 1, 2 ou 3");
    }
    selection();
}


void rechercheId(int identifiant) {
    dictionnaire traduction = rechercheIdentifiant(identifiant);
    accesJaponais(traduction);
    accesFrancais(traduction);
}

void rechercheMot(string motFr) {
    dictionnaire traduction = rechercheJaponais(motFr);
    accesJaponais(traduction);
}

void traduire(string motJap) {
    dictionnaire traduction = rechercheTraduction(motJap);
    accesFrancais(traduction);
}

void lecturedictionnaire(string nomFichier) {
    FILE * dico = NULL; // Le pointeur de fichier qui va contenir notre fichier
    dico = fopen(nomFichier, "r"); // On ouvre le dictionnaire en lecture seule
    // On vérifie si on a réussi à ouvrir le dictionnaire
    if (dico == NULL) usage(nomFichier, "Impossible de charger le dictionnaire de mots"); // Si on n'a PAS réussi à ouvrir le fichier
    int lu = 0;
    char ligne[TAILLE_MAX] = ""; // ligne vide de taille TAILLE_MAX
    while((lu = fgets(ligne, TAILLE_MAX, dico)) != NULL) {
         // On lit maximum TAILLE_MAX caractères du dico, on stocke le tout dans "ligne"
        int id = recupereIdentifiant(ligne);
        japonais Jap = recupereJaponais(ligne, id);
        francais Fr = recupereFrancais(ligne, id);
        japonais_français = pushTraduction(Jap, Fr, japonais_français);
    }
    fclose(dico);
}

dictionnaire rechercheTraduction(string motJaponais) {
    printf("Vous souhaitez traduire en Francais : %s\n\n", motJaponais);
    Entry * recherche = japonais_français;
    while(recherche != NULL) {
        if(my_strcmp(form(recherche).form,motJaponais) == 0 || my_strcmp(form(recherche).secondform, ajoutCrochet(motJaponais)) == 0) {
            /* Si l'élément a la valeur recherchée, on renvoie son adresse */
            return recherche;
        }
        recherche = cdr(recherche);
    }
    return NULL;
}
dictionnaire rechercheJaponais(string motFrancais) {
    printf("Vous souhaitez traduire en Japonais : %s\n\n", motFrancais);
    Entry * recherche = japonais_français;
    while(recherche != NULL) {
        Translate * francais = traductions(recherche);
        while(francais != NULL) {
            if(strstr(form(francais), motFrancais)) {
                /* Si l'élément a la valeur recherchée, on renvoie son adresse */
                return recherche;
            }
            francais = cdr(francais);
        }
        recherche = cdr(recherche);
    }
    return NULL;
}

dictionnaire rechercheIdentifiant(int identifiant) {
    printf("Vous souhaitez voir la traduction pour l'identifiant : %i\n\n", identifiant);
    Entry * recherche = japonais_français;
    while(recherche != NULL) {
        if(form(recherche).id == identifiant) {
            /* Si l'élément a la valeur recherchée, on renvoie son adresse */
            return recherche;
        }
        recherche = cdr(recherche);
    }
    return NULL;
}


char * ajoutCrochet(const char * S) {
    if(!S) return NULL;
    char * res = malloc(strlen("[") + strlen(S) + strlen("]") + 1);
    if (res) {
        strcpy(res, "[");
        strcat(res, S);
        strcat(res, "]");
    }
    return res;
}

void accesFrancais(dictionnaire traduction) {
    if(!estVide(traduction)) { // protege en cas de liste vide
        Translate * francais = traductions(traduction);
        int i = 1;
        while(francais != NULL) {
            printf("Traduction Fr %i: %s\n\n", i,form(francais));
            i++;
            francais = cdr(francais);
        }
    } else {
        printf("%s\n\n", "Aucune traduction trouvé !");

    }
}

void accesJaponais(dictionnaire traduction) {
    if(!estVide(traduction)) { // protege en cas de liste vide
        japonais jap = form(traduction);
        printf("Traduction Jap : %s\n", jap.form);
        if(jap.secondform) printf("Traduction Jap secondaire : %s\n\n", jap.secondform);
    } else {
        printf("%s\n\n", "Aucune traduction trouvé !");

    }
}

int recupereIdentifiant(string ligne) {
    int id = -1;
    char * P = strdup(ligne);
    while(P && * P != '1') P++;
    id = atoi(P);
    return id;
}

japonais recupereJaponais(string ligne, int id) {
    //source :
    //https://waytolearnx.com/2019/09/decouper-une-chaine-de-caractere-en-c.html#:~:text=%5B%5D%20%3D%20%22%20%22%3B-,char%20d%5B%5D%20%3D%20%22%20%22%3B,le%20caract%C3%A8re%20du%20prochain%20mot.
    japonais J = {};
    pointeur = strtok(strdup(ligne), d);
    while(pointeur != NULL && pointeur[0] != separateur) {
        string mot = strdup(pointeur);
        if(pointeur[0] == crochet1) {
            J.secondform = mot;
        }
        else J.form = mot;
        pointeur = strtok(NULL, d);
    }
    pointeur = NULL;
    J.id = id;
    return J;
}

francais recupereFrancais(string ligne, int id) {
    francais F = NULL;
    char * P = strdup(ligne);
    while(* P != separateur) {
        P++;
    };
    string cdr = supprimerCategorie(P);
    int compte = 0;
    pointeur = strtok(strdup(cdr), "/");
    while(pointeur != NULL) {
        compte++;
        pointeur = strtok(NULL, "/");
    }
    pointeur = strtok(strdup(cdr), "/");
    while(pointeur != NULL) {
        string motfrancais = supprimerCategorie(pointeur);
        if(--compte != 0) {
            F = pushFrancais(motfrancais, id, F);
        };
        pointeur = strtok(NULL, "/");
    }
    pointeur = NULL;
    return F;
}

string supprimerCategorie(string ligne) {
    char * P = ligne;
    while (* P == separateur) P++;
    if(* P == parenthese1) {
        while(* P != parenthese2) {
            P++;
        }
        return supprimerCategorie(++P);
    }
    return ligne;
}

francais pushFrancais(string form, int id, francais nouvelEntree) {
    francais new = malloc(sizeof(Translate)) ;
    if (! new) usage("pushFrancais", "cons : manque de RAM") ;
    new -> form = form ;
    new -> id = id;
    new -> cdr = nouvelEntree ;
    return new ;
}

dictionnaire pushTraduction(japonais form, francais traductions, dictionnaire nouvelEntree) {
    dictionnaire new = malloc(sizeof(Entry)) ;
    if (! new) usage("pushTraduction", "cons : manque de RAM") ;
    new -> form = form ;
    new -> traductions = traductions;
    new -> cdr = nouvelEntree ;
    return new ;
}

int my_strcmp(const string S1, const string S2){
    int compare = 0;
    int i;
    if(S1 == NULL || S2 == NULL) { // Permet de corriger l'erreur des string null
        return S1 == NULL ? -1 : 1;
    }
    for(i = 0; S1[i] == S2[i] && S1[i] != '\0'; i++);
    if(S1[i] > S2[i]){
        compare = 1;
//        printf("\n%s est superieur à %s\n", S1, S2);
    }
    else if(S1[i] < S2[i]) {
        compare = -1;
//        printf("\n%s est inferieur à %s\n", S1, S2);
    }
    else {
        compare = 0;
//        printf("\n%s est égale à %s\n", S1, S2);
    }
    return compare;
}

int estVide(void * liste) {
    return (liste == NULL) ? 1 : 0;
}

void usage(const string E, const string D) {
    printf("Erreur : %s\n", E);
    printf("Detail : %s\n", D);
    exit(1) ;
}

