#include <gtk/gtk.h>
#include "header.h"

void afficher_menu_ppal()
{


GtkWidget *menu = NULL;
GtkWidget *tableau=NULL;

GtkButton *nouvelle_partie=NULL;
GtkButton *reprendre_partie=NULL;
GtkButton *instructions=NULL;
GtkButton *quitter=NULL;

GtkWidget* imagenouvellepartie=NULL;
GtkWidget* imagereprendrepartie=NULL;
GtkWidget* imageinstructions=NULL;
GtkWidget* imagequitter=NULL;





  /* Create the main window */
  menu = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  tableau=gtk_table_new(5,1,FALSE);

    nouvelle_partie=gtk_button_new();
    imagenouvellepartie=gtk_image_new_from_file("image_nouvelle_partie.jpg");
    gtk_button_set_image(nouvelle_partie,imagenouvellepartie);

    reprendre_partie=gtk_button_new();
    imagereprendrepartie=gtk_image_new_from_file("image_reprendre_partie.jpg");
    gtk_button_set_image(reprendre_partie,imagereprendrepartie);

    instructions=gtk_button_new();
    imageinstructions=gtk_image_new_from_file("image_instruction.jpeg");
    gtk_button_set_image(instructions, imageinstructions);

    quitter=gtk_button_new();
    imagequitter=gtk_image_new_from_file("image_boutton_quitter.jpeg");
    gtk_button_set_image(quitter, imagequitter);


  /* nouvelle_partie=gtk_button_new_with_label("nouvelle partie");
  reprendre_partie=gtk_button_new_with_label("reprendre partie");
  instructions=gtk_button_new_with_label("instructions");
  quitter=gtk_button_new_with_label("quitter"); */

  gtk_table_attach_defaults(tableau,nouvelle_partie,0,1,1,2);
  gtk_table_attach_defaults(tableau,reprendre_partie,0,1,2,3);
  gtk_table_attach_defaults(tableau,instructions,0,1,3,4);
  gtk_table_attach_defaults(tableau,quitter,0,1,4,5);

  gtk_container_add(menu,tableau);

// associer les évènements aux boutons
  g_signal_connect(nouvelle_partie,"clicked",lancer_nouvelle_partie,NULL);
  g_signal_connect(reprendre_partie,"clicked",reprendrepartie,NULL);
  g_signal_connect(instructions,"clicked",G_CALLBACK(affiche_vue_instruction),NULL);
  g_signal_connect(quitter,"clicked",gtk_main_quit,NULL);


  //gtk_widget_set_size_request(menu,1050,660);


  /* Enter the main loop */
  gtk_widget_show_all (menu);

  }
