#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include "header.h"

void affiche_vue_instruction()
{
    GtkWidget* pWindow;
    GtkWidget* pLabel;
    gchar* sUtf8;
    FILE* fichier = NULL;
    char chaine[C_TAILLE_MAX] = "";
    char s_affichage[10000];

    fichier = fopen("instructions.txt", "r");
    strcpy(s_affichage,"<b></b>\n");
    if (fichier != NULL)
    {
        while (fgets(chaine, C_TAILLE_MAX, fichier) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
        {
            //printf("%s", chaine); // On affiche la chaîne qu'on vient de lire
            //printf("taille chaine %d", strlen(chaine));
            strcat(s_affichage,chaine);
        }

        fclose(fichier);
    }
    else
    {
        strcat(s_affichage,"Fichier d'instructions absent");
    }



    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pWindow),"Instructions de Jeu");
    gtk_window_set_default_size(GTK_WINDOW(pWindow),320,200);

    /* Creation du label avec g_locale_to_utf8 */
    pLabel=gtk_label_new(NULL);

    /* On utilise les balises */
   /* sUtf8 = g_locale_to_utf8("<span face=\"Courier New\"><b>blablabla</b></span>\n"
        "<span font_desc=\"Times New Roman italic 12\" foreground=\"#0000FF\">blablabla</span>\n"
        "<span face=\"Sans\" size=\"16\"><u>blabla</u></span>",
        -1, NULL, NULL, NULL);*/
        /*sUtf8 = g_locale_to_utf8("<span face=\"Courier New 14\"><b>"
        "rtezrtzetz\n"
        "qdfqdfrgq\n"
        "fgdffg\n"
        "</b></span>\n",

        -1, NULL, NULL, NULL);*/
    sUtf8 = g_locale_to_utf8(s_affichage,-1,NULL,NULL,NULL);
    gtk_label_set_markup(GTK_LABEL(pLabel), sUtf8);
    g_free(sUtf8);

    /* On centre le texte */
    gtk_label_set_justify(GTK_LABEL(pLabel), GTK_JUSTIFY_CENTER);

     /* On ajoute le label a l'interieur de la fenetre */
     gtk_container_add(GTK_CONTAINER(pWindow),pLabel);

     /* Affichage de la fenetre et de tout ce qu'il contient */
    gtk_widget_show_all(pWindow);

    /* Connexion du signal
    /* On appelle directement la fonction de sortie de boucle */
    g_signal_connect(G_OBJECT(pWindow),"destroy",G_CALLBACK(gtk_widget_destroy),0);




}
