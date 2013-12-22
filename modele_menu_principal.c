#include "header.h"
#include <stdlib.h>
#include <gtk/gtk.h>
#include "variables globales.h"
void initialiser_nouvelle_variable(jeu_tot* jeu)
{
    jeu->nbpioche=C_NB_CARTE;
    jeu->score_total=0;
    jeu->score_actuel=0;
    int i,j;

// le tableau de jeu est mis à blanc
    for(i=0; i<XMAX; i++)
    {
        for(j=0; j<YMAX; j++)
        {
            tab_jeu[i][j].bas=0;
            tab_jeu[i][j].haut=0;
            tab_jeu[i][j].gauche=0;
            tab_jeu[i][j].droite=0;

        }
    }
}

/*void vider_tableau()
{
    int i,j;
    for (i=0;i<XMAX;i++)
    {
        for (j=0;j<YMAX;j++)
        {
            tab_jeu[i][j].bas=0;
            tab_jeu[i][j].droite=0;
            tab_jeu[i][j].gauche=0;
            tab_jeu[i][j].haut=0;
        }
    }


}
*/

void initialiser_variable(jeu_tot*jeu)
{
    FILE* fichier = NULL;
    int i,j;
    fichier = fopen("test.txt", "r");

    if (fichier != NULL)
    {
        fscanf(fichier, "%d %d %d", &(jeu->score_actuel), &(jeu->score_total), &(jeu->nbpioche));

        for (i=0; i<XMAX; i++)
        {
            for(j=0; j<YMAX; j++)
            {
                fscanf(fichier,"%d %d %d %d ",&tab_jeu[i][j].haut,&tab_jeu[i][j].bas,&tab_jeu[i][j].gauche,&tab_jeu[i][j].droite);
            }
        }

        fclose(fichier);
    }
}
