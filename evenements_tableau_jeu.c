#include "header.h"
#include <stdlib.h>
#include <gtk/gtk.h>
#include "variables globales.h"


//évènement tableau de jeu

void sauver(GtkWidget* sender,jeu_tot* jeu)
{
    FILE* fichier = NULL;
    int i,j;

    fichier = fopen("test.txt", "w+");

    if (fichier != NULL)
    {
        //ecriture des score
        fprintf(fichier, "%d %d %d \n",jeu->score_actuel,jeu->score_total,jeu->nbpioche);
        for (i=0; i<XMAX; i++)
        {
            for(j=0; j<YMAX; j++)
            {
                fprintf(fichier,"%d %d %d %d \n",tab_jeu[i][j].haut,tab_jeu[i][j].bas,tab_jeu[i][j].gauche,tab_jeu[i][j].droite);
            }
        }

        fclose(fichier);
    }
    g_printf ("sauver\n");
}

void fermer_fenetre(GtkButton * sender,GtkWidget* pFormulaire)
//void fermer_fenetre(GtkWidget* sender,jeu_tot* jeu)
{
    //
    //gtk_widget_destroy(target);
    gtk_widget_destroy (GTK_WIDGET (pFormulaire));
    g_printf ("la fin\n");
    //gtk_main_quit();
}

void tourne(GtkWidget* sender,jeu_tot* jeu)
{
    int droite;
    int bas;
    int gauche;
    int haut;


    if (jeu->forme_cree->tourne == 1 )
    {


        droite=jeu->forme_cree->haut;
        bas=jeu->forme_cree->droite;
        gauche=jeu->forme_cree->bas;
        haut=jeu->forme_cree->gauche;

        jeu->forme_cree->haut=haut;
        jeu->forme_cree->bas=bas;
        jeu->forme_cree->gauche=gauche;
        jeu->forme_cree->droite=droite;
        printf("%d\n%d\n%d\n%d",jeu->forme_cree->haut,jeu->forme_cree->bas,jeu->forme_cree->gauche,jeu->forme_cree->droite);
        gtk_container_remove(jeu->aff->vpioche,jeu->aff->image);

        creerimage(jeu);
    }
}

void on_clique_table(GtkWidget* sender,s_position_evenement* p_position )
{
    //printf("case: %d %d \n",p_position->x,p_position->y);

    s_pile* pile_case;
    s_position_evenement xy_case;
    char s_message[250];
    int nb_case;
    //tester s'il reste des cartes dans la pioche
    if(jeu->nbpioche<=0)
    {
        //dialog box d'alerte
        alerte_fin();
        return;
    }

    //xy_case =(s_position_evenement *)malloc(sizeof(s_position_evenement));
    xy_case.x=p_position->x;
    xy_case.y=p_position->y;
    sprintf(s_message,"fct -----> on clique table x: %d y %d",xy_case.x,xy_case.y);
    trace(s_message,2,0);
    pile_case =(s_pile *)malloc(sizeof(s_pile));
    pile_case->longueur=0;

    if (verifier_placage_forme(p_position)==C_FORME_AUTORISEE)
    {
        //placer_forme(p_position);
        // décrementer le nombre de carte
        jeu->nbpioche -=1;

        // afficher l'image sur le tableau de jeu
        afficher_image_tableau_jeu(p_position);

        // génértion d'une nouvelle forme pour la pioche
        //décrementer le nombre de cartes
        //if(jeu->)
        creerforme(jeu);
        // afciher le boution si nécessaire
        afficher_bouton_tourner(jeu);
        // afficher la nouvelle image de la pioche
        gtk_container_remove(jeu->aff->vpioche,jeu->aff->image);
        creerimage(jeu);
        //afficher le nombre de cartes
        modifier_nb_carte(jeu);

            //afficher_score(jeu,jeu->aff->table_score,jeu->aff->table_score_tot);

    }
    else
    {
        remise_a_zero_marquages();
        test_fin=0;

        if( tester_cycle(xy_case, pile_case)==C_CYCLE_VRAI)
        {
            nb_case=recopier_pile(pile_case);
            calcul_scores(nb_case);
            //incrementer le nombre de cartes
            jeu->nbpioche += nb_case/2;
            //afficher dans la vue mise à jour du score
            modifier_score(jeu);
            //afficher le nombre de cartes
            modifier_nb_carte(jeu);
        }
        else
        {
            vider_pile(pile_case);
        }
    }
    free(pile_case);
}
