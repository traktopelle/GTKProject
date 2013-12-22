#include "header.h"
#include <stdlib.h>
#include <gtk/gtk.h>
#include "variables globales.h"
// événements du menu principal


void lancer_nouvelle_partie()
{
//initialisation





// allocations de jeu
    jeu=(jeu_tot*)malloc(sizeof(jeu_tot));

    jeu->forme_cree=(s_forme*)malloc(sizeof(s_forme));
    jeu->aff=(affiche*)malloc(sizeof(affiche));

//
    initialiser_nouvelle_variable(jeu);

// appeller la fenetre de jeu
    creerwin(jeu);






}

void reprendrepartie()
{


//allocations mémoire
    jeu=(jeu_tot*)malloc(sizeof(jeu_tot));
    jeu->forme_cree=(s_forme*)malloc(sizeof(s_forme));

    jeu->aff=(affiche*)malloc(sizeof(affiche));



    initialiser_variable(jeu);
    creerwin(jeu);


}
