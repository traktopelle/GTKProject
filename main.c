#include "header.h"
#include <stdlib.h>
#include <gtk/gtk.h>

s_forme tab_jeu[XMAX][YMAX]; //Tableau de jeu, déclaré en variable globale
jeu_tot* jeu;
int test_fin;
int main (int argc, char *argv[])
{

    gtk_init (&argc, &argv);
    afficher_menu_ppal();

    gtk_main ();
    return EXIT_SUCCESS;

}
void trace(char* s_message, int niveau,int fermeture)
{
    static FILE *fp =NULL;
    time_t timestamp;
    struct tm * t;

    timestamp = time(NULL);
    t = localtime(&timestamp);




    if (fermeture == 1)
    {
        fclose(fp);
        exit(0);
    }
    if (fp==NULL)
    {
        fp=fopen("log.txt","w");
    }
    if(fp==NULL)
    {
        printf("fichier trace absent\n");
        exit(0);
    }
    if (niveau <= C_NIVEAU_TRACE)
    {
            fprintf(fp,"%02u:%02u:%02u--> %s\n",t->tm_hour, t->tm_min,t->tm_sec,s_message);
    }


}
