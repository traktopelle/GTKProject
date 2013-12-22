#include "header.h"
#include <stdlib.h>
#include "variables globales.h"

void creerforme_(jeu_tot* jeu)
{
    char s_message[250];
    static FILE *fp =NULL;
    char nm_fic[100]="cycle2.txt";
    int x,y;


    if (fp==NULL)
    {
        fp=fopen(nm_fic,"r");
    }
    if(fp==NULL)
    {
        printf("fichier cycle absent\n");
        exit(0);
    }


    if (fscanf(fp, "%d %d %d %d %d %d", &x,&y,&jeu->forme_cree->gauche,&jeu->forme_cree->haut,&jeu->forme_cree->droite,&jeu->forme_cree->bas)>0)
    {

    }
    else
    {
        fclose(fp);
        fp=fopen("nm_fic","r");

        fscanf(fp, "%d %d %d %d %d %d", &x,&y,&jeu->forme_cree->gauche,&jeu->forme_cree->haut,&jeu->forme_cree->droite,&jeu->forme_cree->bas);
    }
    sprintf(s_message,"Coordonnées de la case généree:  x=%d y=%d ",x,y);
    trace(s_message,4,0);


}
void fct_test_cycles()
{
int x,y,haut,bas,gauche,droite;
FILE* fichier = NULL;
char s_message[250];
// pour les testss
s_position_evenement position;
s_pile pile_case;
pile_case.longueur=0;

//bouchon
for (x=0;x<XMAX;++x)
{
    for(y=0;y<YMAX;++y)
    {
        tab_jeu[x][y].bas=0;
        tab_jeu[x][y].haut=0;
        tab_jeu[x][y].gauche=0;
        tab_jeu[x][y].droite=0;
        tab_jeu[x][y].marque=0;
    }
}

    fichier = fopen("test.txt", "r");

    if (fichier != NULL)
    {
        while(fscanf(fichier, "%d %d %d %d %d %d", &x, &y, &gauche,&haut,&droite,&bas)!=EOF)
        {


        printf("x: %d, y: %d  %d %d %d %d \n", x,y,gauche,haut,droite,bas);
        tab_jeu[x][y].bas=bas;
        tab_jeu[x][y].haut=haut;
        tab_jeu[x][y].gauche=gauche;
        tab_jeu[x][y].droite=droite;
        }
        fclose(fichier);
    }
position.x=1;
position.y=1;
printf(" Status de tester cycle %d\n", tester_cycle(position, &pile_case));
  while (pile_case.longueur >0)
    {
        x= pile_case.debut->x;
        y= pile_case.debut->y;
        depiler(&pile_case);

        sprintf(s_message,"x %d y %d",x,y);
        trace(s_message,0);


    }


}
