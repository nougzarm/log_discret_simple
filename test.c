#include "test.h"

/* En fonction de la valeur de choix_test :
    1. Algorithme pas de bébé-pas de géant avec paramètre t=isqrt(|G|)
    2. Algorithme de Rho-Pollard sans mémoire.
*/

int main() {
    // CHOIX DE L'OPÉRATION --------------------------------------------------------
    int choix_test = 1;

    // CONFIGURATION - CHOIX DU GROUPE (Z/pZ)* et d'un générateur g -------------------
    int p = 383;
    int g = 2;
    int h = 229;

    // AFFICHAGE DE LA CONFIGURATION -----------------------------------------------
    printf("----------------------------------------------------------------- \n");
    printf("Définitions :\n  - Groupe ((Z/%dZ)*,x), d'ordre %d-1=%d\n", p, p, p-1);
    printf("  - Générateur g = %d", g);
    printf("\n  - Element dont on cherche le log discret : h = %d", h); printf("\n\n");
    
    // LANCEMENT DE L'ALGORITHME ---------------------------------------------------
    test(choix_test, h, g, p);
    printf("\n----------------------------------------------------------------- \n");

    return 1;
}


// Définition des tests
void test(int choix_test, int h, int g, int p){
    if(choix_test == 1){
        int x = pas_bebe_pas_geant(h, g, p, racine_carree_entiere_mn(p-1));
        printf("D'après l'algorithme pas de bébé-pas de géant :\n  - le log discret de %d en base %d est x = %d", h, g, x);
        int verif = puissance_modulo(g, x, p);
        printf("\n  - Vérification : g^x =  %d", verif);

    }
    else if(choix_test == 2){
        RP_element y_0; 
        y_0.alpha = 0; y_0.beta = 0; y_0.valeur = 1;
        int x = rho_pollard_sans_memoire(y_0, h, g, p);
        if(x == -1){
            printf("Echec de l'algorithme : Le couple de betas trouvé ne satisfait pas la condition du pgcd");
        }
        else{
            printf("D'après l'algorithme de Rho-Pollard (sans mémoire) :\n  - le log discret de %d en base %d est x = %d", h, g, x);
            int verif = puissance_modulo(g, x, p);
            printf("\n  - Vérification : g^x = %d", verif);
        }
    }
    return;
}