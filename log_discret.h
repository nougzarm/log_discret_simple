#ifndef LOG_DISCRET_INCLUDED
#define LOG_DISCRET_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*  Structure permettant de décomposer y = g^alpha * h^beta 
    utilisée dans l'algorithme de Rho-Pollard */
typedef struct{
    int alpha;
    int beta;
    int valeur;
}RP_element;


/*  Structure de liste (p.ex pour stocker les valeurs de la phase de précalcul   
    dans l'algorithme pas de bébé-pas de géant) */
typedef struct{
    int* element;
    int taille;
}liste_stockage;


//  Fonctions principales
int pas_bebe_pas_geant(int h, int g, int p, int t);                     //  Algo Pas de bébé-pas de géant
int rho_pollard_sans_memoire(RP_element y_0, int h, int g, int p);      //  Algo Rho-Pollard sans mémoire


//  Fonctions intérmédiaires
RP_element F_aleatoire(RP_element y, int h, int g, int p);              //  Pseudo-aléatoire pour Rho-Pollard
liste_stockage precalcul(int h, int g, int p, int t);                   //  Précalculs pour Pas de bébé-Pas de géant


//  Fonctions primaires
int modulo(int a, int b);                       //  Renvoie a modulo b
int puissance_modulo(int m, int e, int p);      //  Renvoie m^e modulo p
int inverse(int a, int p);                      //  Inverse de a dans Z/pZ lorsque pgcd(a,p)=1
int pgcd(int a, int b);                 //  PGCD
int partie_entiere(double n);           //  Partie entière de n
int racine_carree_entiere_mn(int n);    //  Racine carrée entière de n (algo naïf)

#endif // LOG_DISCRET_INCLUDED