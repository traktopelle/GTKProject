#include "header.h"
#include <stdlib.h>
#include <gtk/gtk.h>
#include "variables globales.h"



char* associer_fichier_image (int haut,int bas,int gauche,int droite)
{
char* nm_fic=NULL;

nm_fic=malloc((250)*sizeof(char));

// par sécurité on met le fond
    strcpy(nm_fic,"fond.jpg");
    /*if  ((haut==0) &&  (bas==0) && (gauche==0) && (droite==0))
    {
        strcpy(nm_fic,"fond.jpg");
    }*/

    if ((haut==1) &&  (bas==1) && (gauche==0) && (droite==0))
    {
        strcpy(nm_fic,"vertical_g.jpg");
    }

    if ((haut==1) &&  (bas==0) && (gauche==1) && (droite==0))
    {
        strcpy(nm_fic,"gauche_haut_g.jpg");
    }

    if ((haut==1) &&  (bas==0) && (gauche==0) && (droite==1))
    {
        strcpy(nm_fic,"droite_haut_g.jpg");
    }

    if ((haut==0) &&  (bas==1) && (gauche==1) && (droite==0))
    {
        strcpy(nm_fic,"gauche_bas_g.jpg");
    }

    if ((haut==0) &&  (bas==1) && (gauche==0) && (droite==1))
    {
        strcpy(nm_fic,"droite_bas_g.jpg");
    }

    if ((haut==0) &&  (bas==0) && (gauche==1) && (droite==1))
    {
        strcpy(nm_fic,"horizontal_g.jpg");
    }

    if ((haut==1) &&  (bas==1) && (gauche==1) && (droite==1))
    {
        strcpy(nm_fic,"croix_g.jpg");
    }

    if ((haut==1) &&  (bas==1) && (gauche==1) && (droite==0))
    {
        strcpy(nm_fic,"croix_gauche.jpg");
    }

    if ((haut==1) &&  (bas==1) && (gauche==0) && (droite==1))
    {
        strcpy(nm_fic,"croix_droite.jpg");
    }

    if ((haut==1) &&  (bas==0) && (gauche==1) && (droite==1))
    {
        strcpy(nm_fic,"croix_haut.jpg");
    }

    if ((haut==0) &&  (bas==1) && (gauche==1) && (droite==1))
    {
        strcpy(nm_fic,"croix_bas.jpg");
    }

return nm_fic;
}



void creerimage(jeu_tot*jeu)
{
    GtkWidget* image_pioche=NULL;
    char* nm_fic;

    nm_fic=associer_fichier_image (jeu->forme_cree->haut,jeu->forme_cree->bas,jeu->forme_cree->gauche,jeu->forme_cree->droite);
    image_pioche=gtk_image_new_from_file(nm_fic);
    free(nm_fic);
    jeu->aff->image=image_pioche;
    gtk_container_add(jeu->aff->vpioche,jeu->aff->image);
    gtk_widget_show_all(jeu->aff->image);


}










