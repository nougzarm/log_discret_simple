#include "log_discret.h"

// FONCTIONS INTERMEDIAIRES ------------------------------------------------
int modulo(int a, int b){
    return a%b + (b * (a%b<0));
}

int puissance_modulo(int m, int e, int p){
    int result = 1;
    for (int i = 1; i <= e; i++){
        result = modulo(result, p)*m;
    }
    return modulo(result, p);
}

int inverse(int a, int p){
    int r0 = p, r1 = a, r2 = r0%r1;
    int v0 = 0, v1 = 1, v2 = v0 - (r0/r1)*v1;
    while ( r2 != 0 ){
        r0 = r1;
        r1 = r2;
        r2 = modulo(r0, r1);
        v0 = v1;
        v1 = v2;
        v2 = v0 - (r0/r1)*v1;
    }
    v1 = modulo(v1, p);
    return v1;
}

int pgcd(int a, int b){
    int r0 = b, r1 = a, r2 = r0%r1;
    while ( r2 != 0 ){
        r0 = r1;
        r1 = r2;
        r2 = modulo(r0, r1);
    }
    return r1;
}

int partie_entiere(double n){
    int partie_ent = (int)floor(n);
    return partie_ent;
}

int racine_carree_entiere_mn(int n){
    int racine = partie_entiere(sqrt((double)n));
    return racine;
}
// ---------------------------------------------------------------


// RHO-POLLARD ---------------------------------------------------
RP_element F_aleatoire(RP_element y, int h, int g, int p){
    RP_element image;
    image.alpha = y.alpha; 
    image.beta = y.beta;
    int k = y.valeur%3;
    if(k == 1){
        image.valeur = modulo(h*y.valeur, p);
        image.beta++;
    }
    else if(k == 0){
        image.valeur = modulo(y.valeur*y.valeur, p);
        image.alpha = 2*image.alpha;
        image.beta = 2*image.beta;
    }
    else{
        image.valeur = modulo(g*y.valeur, p);
        image.alpha++;
    }
    return image;
}

int rho_pollard_sans_memoire(RP_element y_0, int h, int g, int p){
    RP_element premier = F_aleatoire(y_0, h, g, p);
    RP_element second = F_aleatoire(premier, h, g, p);
    int indice = 1; //  Pas nécessaire
    while( premier.valeur != second.valeur ){
        premier = F_aleatoire(premier, h, g, p);
        second = F_aleatoire(F_aleatoire(second, h, g, p), h, g, p);
        indice++;
    }
    int diff_beta = modulo(second.beta - premier.beta, p-1);
    int x = -1;
    if( pgcd(diff_beta, p-1) == 1 ){
        x = modulo((premier.alpha - second.alpha)*inverse(diff_beta, p-1), p-1);
    }
    return x;
}
// ---------------------------------------------------------------


// Pas de bébé-pas de Géant --------------------------------------
liste_stockage precalcul(int h, int g, int p, int t){
    liste_stockage liste_precalcul;
    liste_precalcul.element = calloc(t, sizeof(int));
    liste_precalcul.taille = t;
    liste_precalcul.element[0] = 1;
    for(int i=1; i < t; i++){
        liste_precalcul.element[i] = modulo(liste_precalcul.element[i-1]*g, p);
    }
    return liste_precalcul;
}


int pas_bebe_pas_geant(int h, int g, int p, int t){
    liste_stockage liste_precalcul = precalcul(h, g, p, t);
    int inv_gt = inverse(puissance_modulo(g, t, p), p);
    int x;
    int quotient = 0;
    int reste = 0;
    for(int j = 0; j <= p/t; j++){
        int etat = 0;
        for(int i = 0; i < t; i++){
            if(modulo(h*puissance_modulo(inv_gt, j, p), p) == liste_precalcul.element[i]){
                etat = 1;
                quotient = j;
                reste = i;
                break;
            }
        }
        if(etat == 1){
            break;
        }
    }
    x = quotient*t+reste;
    free(liste_precalcul.element);
    return x;
}
// ---------------------------------------------------------------