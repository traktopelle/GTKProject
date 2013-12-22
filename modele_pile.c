#include "header.h"
#include <stdlib.h>

//#include "variables globales.h"

void empiler(s_pile* p_pile, s_position_evenement s_position )
{
    char s_message[250];
    trace("fct ----> empiler",2,0);
    s_maillon* nouveau;

    // verifier que la donnée n'est pas déjà dans la pile
    if(verif_presence(p_pile,s_position)==0)
    {



    nouveau=(s_maillon*)malloc(sizeof(s_maillon));

    nouveau->suivant=NULL;

    nouveau->x = s_position.x;
    nouveau->y = s_position.y;

    nouveau->suivant=p_pile->debut;
    p_pile->debut=nouveau;
    p_pile->longueur++;
    sprintf(s_message,"fct empiler taille pile %d x %d y %d", p_pile->longueur,s_position.x,s_position.y);
    trace(s_message,2,0);
    }
}

 void depiler(s_pile* p_pile)
{

    s_maillon* detruire;
    detruire=p_pile->debut;
    p_pile->debut = p_pile->debut->suivant;

    free (detruire);
    p_pile->longueur--;


}

void vider_pile (s_pile* p_pile)
{
    while (p_pile->longueur>0)
    {
        depiler(p_pile);

    }
}
int verif_presence(s_pile *pile,s_position_evenement xy)
{

    s_maillon* p_maillon;
    int longueur;
    p_maillon=pile->debut;
    longueur=pile->longueur;
    while(longueur >0)
    {
        if (p_maillon->x == xy.x && p_maillon->y == xy.y)
        {
            return -1;
        }
        p_maillon=p_maillon->suivant;
        longueur--;
    }

    return 0;
}
