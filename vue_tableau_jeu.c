#include "header.h"
#include <stdlib.h>
#include <gtk/gtk.h>
#include "variables globales.h"

// affichage fenêtre de jeu
void creerwin(jeu_tot* jeu)
{
    GtkWidget* win=NULL;
    GtkWidget* vbox=NULL;
    GtkWidget* hbox=NULL;
    GtkWidget* hbox_score=NULL;
    GtkWidget* vpioche=NULL;
    GtkWidget* nbrepioche=NULL;
    GtkWidget* table_score=NULL;
    GtkWidget* table_score_tot=NULL;

    char nb[100];

    GtkTable* table=NULL;
    GtkTable* table_jeu=NULL;
    GtkWidget* tabledroite=NULL;

    GtkWidget* imagewin=NULL;

    GtkWidget* tourner=NULL;

//creer la fenêtre

    win=gtk_window_new(GTK_WINDOW_TOPLEVEL);

 //creer les objets de la fenêtre
    vbox=gtk_vbox_new(FALSE,0);
    hbox=gtk_hbox_new(FALSE,0);
    hbox_score=gtk_hbox_new(TRUE,0);
    table=gtk_table_new(1,1,FALSE);

    vpioche=gtk_vbox_new(TRUE,0);

    tabledroite=gtk_table_new(11,1,TRUE);
    table_score=gtk_table_new(1,1,TRUE);
    table_score_tot=gtk_table_new(1,1,TRUE);

    table_jeu=gtk_table_new(12,8,FALSE);
    tourner=gtk_button_new();

// hierarchieser les objets

    gtk_container_add(win,hbox);

        gtk_box_pack_start(hbox,table,TRUE, FALSE, 0);
            gtk_container_add(table,vbox);
                //affichage de la pioche et du score
                gtk_container_add(vbox,hbox_score);
                    gtk_container_add(hbox_score,vpioche);
                         // nombre de carte
                        sprintf(nb,"<b>%d</b>",jeu->nbpioche);
                        nbrepioche=gtk_label_new(NULL);
                        gtk_label_set_markup(nbrepioche,nb);
                        gtk_container_add(vpioche,nbrepioche);

                        gtk_container_add(vpioche,tourner);
                    //scores
                    gtk_container_add(hbox_score,table_score);
                    gtk_container_add(hbox_score,table_score_tot);


                // affichage du tableua de jeu
                gtk_container_add(vbox,table_jeu);


        gtk_box_pack_start(hbox,tabledroite,TRUE, FALSE, 0);


// sauvegarde des objets

     jeu->aff->vbox=vbox;
     jeu->aff->hbox=hbox_score;
     jeu->aff->vpioche=vpioche;
     jeu->aff->table=table_jeu;
     jeu->aff->table_score=table_score;
     jeu->aff->table_score_tot=table_score_tot;
     jeu->aff->btn_tourner=tourner;
     jeu->aff->pnb_carte=nbrepioche;
     jeu->aff->pwin_tableau_jeu=win;

// mise en forme panneau de droite (association évènement boutons)
    afficher_panneau_droite(tabledroite,win,jeu);


 //mise en forme pioche (vpioche)
    //générer aleatoirement une forme pour la pioche
    creerforme(jeu);
    afficher_bouton_tourner(jeu);

// creer le widget pioche et affiche l'image de la pioche (vpioche)

    creerimage(jeu);

// afficher le scores dans table_score
    afficher_score(jeu, table_score,table_score_tot );


 // mise en forme panneau de jeu
    imagewin=gtk_image_new_from_file("win.jpg");
    gtk_table_attach_defaults(table,imagewin,0,1,0,1);
    afficher_table_jeu(jeu,table_jeu);


// evenements du bouton tourner
    g_signal_connect(tourner,"clicked",tourne,jeu);

// dimension de la fenêtre

    gtk_widget_set_size_request(win,1050,660);

    gtk_widget_show_all(win);


}
void afficher_panneau_droite(GtkWidget* tabledroite,GtkWidget* win,jeu_tot* jeu )
{
    GtkWidget* retourmenu=NULL;
    GtkWidget* imageretourmenu=NULL;
    GtkWidget*sauvegarde=NULL;
    GtkWidget* imagesauvegarde=NULL;
    GtkWidget* image=NULL;
    // mise en forme panneau de droite

// creer le bouton de sauvegarde
    sauvegarde=gtk_button_new();
    imagesauvegarde=gtk_image_new_from_file("imagesauvegarde.jpg");
    gtk_button_set_image(sauvegarde,imagesauvegarde);

// creer le bouton retour au menu ppal
    retourmenu=gtk_button_new();
    imageretourmenu=gtk_image_new_from_file("imageretourmenu.jpg");
    gtk_button_set_image(retourmenu,imageretourmenu);

// couleur de fond des boutons
    GdkColor color;
    color.pixel=32;
    color.blue=0;
    color.green=25000;
    color.red=60000;
    gtk_widget_modify_bg(retourmenu,GTK_STATE_NORMAL,&color);
    gtk_widget_modify_bg(sauvegarde,GTK_STATE_NORMAL,&color);

    image=gtk_image_new_from_file("image_droite.bmp");

    gtk_table_attach_defaults(tabledroite,retourmenu,0,1,3,4);
    gtk_table_attach_defaults(tabledroite,sauvegarde,0,1,4,5);
    gtk_table_attach_defaults(tabledroite,image,0,1,0,11);


    // association des évènement de la fenêtre



    //g_signal_connect(G_OBJECT(retourmenu),"clicked",G_CALLBACK(retourmenu),win);
    g_signal_connect(G_OBJECT(retourmenu),"clicked",G_CALLBACK(fermer_fenetre),win);
    g_signal_connect(G_OBJECT(sauvegarde),"clicked",sauver,jeu);
}

void afficher_table_jeu(jeu_tot* jeu,GtkWidget* table)
{

    GtkWidget* button;
    GtkWidget* image=NULL;
    s_position_evenement* xy_case;

    char* nm_fic = NULL;


    int i;
    int j;



    for (i=0; i<XMAX; i++)
    {
        for(j=0; j<YMAX; j++)
        {

            GdkColor color;
            color.pixel=32;
            color.blue=0;
            color.green=25000;
            color.red=60000;

            button=gtk_button_new();
            gtk_widget_modify_bg(button,GTK_STATE_NORMAL,&color);

            // afficher l'image corresponsant à la donnée
            nm_fic = associer_fichier_image(tab_jeu[i][j].haut,tab_jeu[i][j].bas,tab_jeu[i][j].gauche,tab_jeu[i][j].droite);

            image=gtk_image_new_from_file(nm_fic);
            free(nm_fic);
            gtk_button_set_image(button,image);
            gtk_table_attach_defaults(table,button,i,i+1,j,j+1);

            xy_case=(s_position_evenement*)malloc(sizeof(s_position_evenement));
            xy_case->x=i;
            xy_case->y=j;
            jeu->aff->btn_tab_jeu[i][j]=button;
            g_signal_connect(button,"clicked",G_CALLBACK(on_clique_table),xy_case);

        }
    }

}


void afficher_bouton_tourner(jeu_tot*jeu)
{
     //afficher bouton tourner
    GtkWidget* imageboutton=NULL;

    printf("fct tourner \n");



    if (jeu->forme_cree->tourne==1)
    {
        printf("je passe dans la boucle");


        imageboutton=gtk_image_new_from_file("bouttontourner.jpg");

    }
    else
    {
        imageboutton=gtk_image_new_from_file("bouttontournerF.jpg");
        printf("image grise");

    }

    gtk_button_set_image(jeu->aff->btn_tourner,imageboutton);

}

void afficher_image_tableau_jeu(s_position_evenement* xy_case)
{
     //afficher bouton tourner
    GtkWidget* imageboutton=NULL;
    char* nm_fic;
    char s_message[250];
    //GList *pList;
    //GtkWidget *pTempEntry;

    int i,j;


    i=xy_case->x;
    j=xy_case->y;
    sprintf(s_message,"fct ----> afficher image bouton i %d j %d \n",i,j);
    trace(s_message,4,0);

    //nm_fic = associer_fichier_image(jeu->forme_cree->haut,jeu->forme_cree->bas,jeu->forme_cree->gauche,jeu->forme_cree->droite);
    nm_fic = associer_fichier_image(tab_jeu[i][j].haut,tab_jeu[i][j].bas,tab_jeu[i][j].gauche,tab_jeu[i][j].droite);

    //imageboutton=gtk_image_new_from_file(nm_fic);
    imageboutton=gtk_image_new_from_file(nm_fic);
    sprintf(s_message,"nm_fic %s\n",nm_fic);
    trace(s_message,4,0);
    sprintf(s_message,"nom widget %s\n",gtk_widget_get_name(jeu->aff->btn_tab_jeu[i][j]));
    trace(s_message,4,0);
     /* Recuperation de la liste des elements que contient la GtkVBox */
    //pList = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)jeu->aff->btn_tab_jeu[i][j]));
    //pTempEntry = GTK_WIDGET(pList->data);
    //gtk_image_set_from_file(pTempEntry,nm_fic);
    gtk_button_set_image((GtkWidget*)jeu->aff->btn_tab_jeu[i][j],imageboutton);
    //gtk_button_set_image((GtkWidget*)jeu->aff->btn_tab_jeu[i][j],imageboutton);
    //gtk_widget_show_all(jeu->aff->btn_tab_jeu[i][j]);
    //gtk_widget_show (jeu->aff->btn_tab_jeu[i][j]);
    free(nm_fic);
 //g_list_free(pList);
}

void afficher_score(jeu_tot*jeu,GtkWidget* table_score,GtkWidget* table_score_tot )
{
    GtkWidget* scoreact=NULL;
    GtkWidget* imagescoreact=NULL;
    GtkWidget* scoretot=NULL;

    GtkWidget* imagescoretot=NULL;
    char score1[100];

    //score actuel
    imagescoreact=gtk_image_new_from_file("imagescoreact.jpg");
    sprintf(score1,"<b>%d</b>",jeu->score_actuel);
    printf("score actuel %s\n",score1);
    scoreact=gtk_label_new(NULL);
    gtk_label_set_markup(scoreact,score1);

    gtk_table_attach_defaults(table_score,scoreact,0,1,0,1);
    gtk_table_attach_defaults(table_score,imagescoreact,0,1,0,1);
    //score total

    imagescoretot=gtk_image_new_from_file("imagescoretot.jpg");

    sprintf(score1,"<b>%d</b>",jeu->score_total);
    scoretot=gtk_label_new(NULL);
    gtk_label_set_markup(scoretot,score1);
    jeu->aff->pLabel_score_act=scoreact;
    jeu->aff->pLabel_score_tot=scoretot;
    printf("score total %d\n",jeu->score_total);
    gtk_table_attach_defaults(table_score_tot,scoretot,0,1,0,1);
    gtk_table_attach_defaults(table_score_tot,imagescoretot,0,1,0,1);
    //gtk_widget_show (table_score);

}

void modifier_score(jeu_tot*jeu)
{
    //GtkWidget* scoreact=NULL;

    //GtkWidget* scoretot=NULL;

    char s_message[250];
    char score1[100];

    //score actuel

    sprintf(score1,"<b>%d</b>",jeu->score_actuel);
    sprintf(s_message,"fct ----> modifier score score actuel %s\n",score1);
    trace(s_message,2,0);
    //scoreact=gtk_label_new(score1);
    //gtk_label_set_text (jeu->aff->pLabel_score_act, score1);
    gtk_label_set_markup(jeu->aff->pLabel_score_act, score1);
    //score total



    sprintf(score1,"<b>%d</b>",jeu->score_total);
    //scoretot=gtk_label_new(score1);
    sprintf(s_message,"fct ----> modifier score score total %d\n",jeu->score_total);
    trace(s_message,2,0);
    //gtk_label_set_text (jeu->aff->pLabel_score_tot, score1);
    gtk_label_set_markup (jeu->aff->pLabel_score_tot, score1);
    //gtk_widget_show (table_score);

}

void modifier_nb_carte(jeu_tot*jeu)
{
    char s_message[250];
    char score1[100];

    //score actuel

    sprintf(score1,"<b>%d</b>",jeu->nbpioche);
    sprintf(s_message,"fct ----> modifier nb carte nb_carte %s\n",score1);
    trace(s_message,2,0);
    //scoreact=gtk_label_new(score1);
    //gtk_label_set_text (jeu->aff->pLabel_score_act, score1);
    gtk_label_set_markup(jeu->aff->pnb_carte, score1);
}

void alerte_fin()
{
    GtkWidget *pAbout;


    /* Creation de la boite de message */
    /* Type : Information -> GTK_MESSAGE_INFO */
    /* Bouton : 1 OK -> GTK_BUTTONS_OK */
    pAbout = gtk_message_dialog_new (GTK_WINDOW(jeu->aff->pwin_tableau_jeu),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "Plus de carte en pioche, fin du jeu");

    /* Affichage de la boite de message */
    gtk_dialog_run(GTK_DIALOG(pAbout));

    /* Destruction de la boite de message */
    gtk_widget_destroy(pAbout);
}
