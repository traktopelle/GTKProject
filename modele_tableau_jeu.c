
#include "header.h"
#include <stdlib.h>
#include <gtk/gtk.h>
#include "variables globales.h"

void creerforme(jeu_tot*jeu)
{
int nb=0;
int alea;

    srand(time(NULL));

while (nb<2)
{


    jeu->forme_cree->haut=rand()%2;
    jeu->forme_cree->bas=rand()%2;
    jeu->forme_cree->gauche=rand()%2;
    jeu->forme_cree->droite=rand()%2;

    nb=jeu->forme_cree->haut+jeu->forme_cree->bas+jeu->forme_cree->gauche+jeu->forme_cree->droite;
}
    alea=rand()%3;
    if (alea==1)
    {
        jeu->forme_cree->tourne=1;
    }
    else
    {
        jeu->forme_cree->tourne=0;
    }

printf("valeur tourne %d\n",jeu->forme_cree->tourne);
}



void placer_forme (s_position_evenement* p_position )
{
    int x, y;

    x=p_position->x;
    y=p_position->y;

    tab_jeu[x][y].haut=jeu->forme_cree->haut;
    tab_jeu[x][y].bas=jeu->forme_cree->bas;
    tab_jeu[x][y].droite=jeu->forme_cree->droite;
    tab_jeu[x][y].gauche=jeu->forme_cree->gauche;



}

int verifier_placage_forme ( s_position_evenement* p_position)
{
    int status =0;
    int x, y;

    x=p_position->x;
    y=p_position->y;

    if( tab_jeu[x][y].haut==0 && tab_jeu[x][y].bas==0 && tab_jeu[x][y].droite==0 && tab_jeu[x][y].gauche==0)
    {
        placer_forme ( p_position);
        status=C_FORME_AUTORISEE;
        trace("fct -----> verifier placage forme pas de forme initiale",2,0);
    }
    else
    {

        // forme cree et tab_jeu doivent avoir des valeur toutes différentes

        if( (jeu->forme_cree->gauche != tab_jeu[x][y].gauche) &&
            (jeu->forme_cree->droite != tab_jeu[x][y].droite) &&
            (jeu->forme_cree->bas != tab_jeu[x][y].bas ) &&
            (jeu->forme_cree->haut != tab_jeu[x][y].haut) )
        {
            tab_jeu[x][y].gauche=1;
            tab_jeu[x][y].droite =1;
            tab_jeu[x][y].haut=1;
            tab_jeu[x][y].bas =1;
            status=C_FORME_AUTORISEE;
            trace("fct -----> verifier placage forme initiale complémentaire",2,0);
        }
        else
        {
            status=C_FORME_REFUSEE;
            trace("fct -----> verifier placage forme initiale non complémentaire",2,0);
        }


    }
    return status;
}


void calcul_scores (int nb_case)
{
    char s_message[250];
    sprintf(s_message,"fct ----> calcule_score nb case %d",nb_case);
    trace(s_message,2,0);
    jeu->score_actuel=nb_case*nb_case;
    jeu->score_total=jeu->score_total+jeu->score_actuel;

}

int recopier_pile (s_pile* p_pile)
{
    int x,y;
    int nb_case;
    char s_message[250];
    s_position_evenement xy_case;
    trace("fct ----> recopier pile",2,0);
    //jeu->score_actuel=0;
    sprintf(s_message,"recopier pile longueur pile %d",p_pile->longueur);
    trace(s_message,2,0);
    nb_case=0;
    while (p_pile->longueur >0)
    {

        x= p_pile->debut->x;
        y= p_pile->debut->y;
        depiler(p_pile);
        sprintf(s_message,"longueur pile %d contenu x %d y %d",p_pile->longueur,x,y);
        trace(s_message,2,0);
        nb_case++;

        tab_jeu[x][y].bas=0;
        tab_jeu[x][y].haut=0;
        tab_jeu[x][y].droite=0;
        tab_jeu[x][y].gauche=0;
        xy_case.x=x;
        xy_case.y=y;
        afficher_image_tableau_jeu(&xy_case);

    }
return nb_case;


}



void remise_a_zero_marquages()
{
    trace("fct -----> raz marquage",2,0);
    int i,j;
    for(i=0;i<XMAX;i++)
    {
        for(j=0;j<YMAX;j++)
        {
            tab_jeu[i][j].marque=0;
        }

    }
}

int tester_cycle (s_position_evenement s_position, s_pile* p_pile)
{
    int status;
    int x,y;
    int i,j;
    char s_message[250];
    s_position_evenement s_position_temp;
    trace("fct ---->tester_cycle",1,0);

    x=s_position.x;
    y=s_position.y;

//RAZ marquages TODO
    /*for(i=0;i<XMAX-1;i++)
    {
        for(j=0;j<YMAX-1;j++)
        {
            tab_jeu[i][j].marque=0;
        }

    }
    */


    //test depart vers le haut
    sprintf(s_message,"tester cycle Coordonnées de la case :  x=%d y=%d ",x,y);
    trace(s_message,2,0);
    if(tab_jeu[x][y].marque==0)
    {
        empiler(p_pile,s_position);
    }


    //si cas composante vers le haut
    if (tab_jeu[x][y].haut==1)
    {
        //sprintf(s_message,"x=%d y=%d Test de la composante vers le haut ",x,y);
        //trace(s_message,2,0);

        //si case du haut dans le jeu
        if(y-1>=0)
        {
            //si case du haut a une composante vers le base
            if(tab_jeu[x][y-1].bas==1)
            {
                // si case du haut pas déjà vue
                if(tab_jeu[x][y-1].marque==0)
                    {
                        sprintf(s_message,"tester cycle vers le haut valide de  x=%d y=%d à x=%d y=%d",x,y,x,y-1);
                        trace(s_message,3,0);
                        //empiler la case, marque comme vue
                        tab_jeu[x][y].marque=1;
                        //empiler(p_pile,s_position);
                        //relancer le test sur case du haut
                        s_position_temp.y=y-1;
                        s_position_temp.x=x;
                        status = tester_cycle (s_position_temp, p_pile);
                    }
                else
                    {
                        //case déjà vue
                        //cycle bouclé correct
                        status=C_CYCLE_VRAI;
                        //sprintf(s_message,"x=%d y=%d Case du haut deja testée", x,y);
                        //trace(s_message,2,0);
                        //test_fin=1;
                    }

            }
            else
            {
                //pas de composante du bas
                //fin du test négatif
                status=C_CYCLE_FAUX;
                test_fin=2;
            }
        }
        else
        {
            //case pas dans le jeu
            //fin du test négatif
            status=C_CYCLE_FAUX;
            test_fin=2;
        }

    }

    if (test_fin !=0)
    {

        return status;
    }
   //test depart vers le droite

    //si cas composante vers le droite
    if (tab_jeu[x][y].droite==1)
    {
        //sprintf(s_message,"x=%d y=%d Test de la composante vers la droite ",x,y);
        //trace(s_message,2,0);
        //si case de droite dans le jeu
        if(x+1<XMAX)
        {
            //si case du droite a une composante vers le gauche
            if(tab_jeu[x+1][y].gauche==1)
            {
                // si case du droite pas déjà vue
                if(tab_jeu[x+1][y].marque==0)
                    {
                        sprintf(s_message,"tester cycle vers la droite valide de  x=%d y=%d à x=%d y=%d",x,y,x+1,y);
                        trace(s_message,3,0);
                        //empiler la case, marque comme vue
                        tab_jeu[x][y].marque=1;
                        //empiler(p_pile,s_position);
                        //relancer le test sur case du haut
                        s_position_temp.x=x+1;
                        s_position_temp.y=y;
                        status = tester_cycle (s_position_temp, p_pile);
                    }
                else
                    {
                        //case déjà vue
                        //cycle bouclé correct
                        status=C_CYCLE_VRAI;
                        //sprintf(s_message,"x=%d y=%d Case de droite deja testée", x,y);
                        //trace(s_message,2,0);
                         //test_fin=1;
                    }

            }
            else
            {
                //pas de composante du bas
                //fin du test négatif
                status=C_CYCLE_FAUX;
                 test_fin=2;
            }
        }
        else
        {
            //case pas dans le jeu
            //fin du test négatif
            status=C_CYCLE_FAUX;
             test_fin=2;
        }

    }
       if (test_fin !=0)
    {

        return status;
    }

    //test depart vers la gauche

    //si cas composante vers le gauche
    if (tab_jeu[x][y].gauche==1)
    {
        //sprintf(s_message,"x=%d y=%d test de la composante vers la gauche ",x,y);
        //trace(s_message,2,0);
        //si case de droite dans le jeu
        if(x>0)
        {
            //si case de gauche a une composante vers le droite
            if(tab_jeu[x-1][y].droite==1)
            {
                // si case du droite pas déjà vue
                if(tab_jeu[x-1][y].marque==0)
                    {
                        sprintf(s_message,"tester cycle vers la gauche valide de  x=%d y=%d à x=%d y=%d",x,y,x-1,y);
                        trace(s_message,3,0);
                        //empiler la case, marque comme vue
                        tab_jeu[x][y].marque=1;
                        //empiler(p_pile,s_position);
                        //relancer le test sur case de gauche
                        s_position_temp.x=x-1;
                        s_position_temp.y=y;
                        status = tester_cycle (s_position_temp, p_pile);
                    }
                else
                    {
                        //case déjà vue
                        //cycle bouclé correct
                        status=C_CYCLE_VRAI;
                        //sprintf(s_message,"x=%d y=%d case de gauche deja testée", x,y);
                        //trace(s_message,2,0);
                        //test_fin=1;
                    }

            }
            else
            {
                //pas de composante du bas
                //fin du test négatif
                status=C_CYCLE_FAUX;
                test_fin=2;
            }
        }
        else
        {
            //case pas dans le jeu
            //fin du test négatif
            status=C_CYCLE_FAUX;
            test_fin=2;
        }
    }

    if (test_fin !=0)
    {

        return status;
    }

    // test depart vers le bas

     //si cas composante vers le bas
    if (tab_jeu[x][y].bas==1)
    {
        //sprintf(s_message,"x=%d y=%d Test de la composante vers le bas ",x,y);
        //trace(s_message,2,0);
        //si case du haut dans le jeu
        if(y+1<YMAX)
        {
            //si case du bas a une composante vers le haut
            if(tab_jeu[x][y+1].haut==1)
            {
                // si case du haut pas déjà vue
                if(tab_jeu[x][y+1].marque==0)
                    {
                        sprintf(s_message,"tester cycle vers le bas valide de  x=%d y=%d à x=%d y=%d",x,y,x,y+1);
                        trace(s_message,3,0);
                        //empiler la case, marque comme vue
                        tab_jeu[x][y].marque=1;
                        //empiler(p_pile,s_position);
                        //relancer le test sur case du haut
                        s_position_temp.y=y+1;
                        s_position_temp.x=x;
                        status = tester_cycle (s_position_temp, p_pile);
                    }
                else
                    {
                        //case déjà vue
                        //cycle bouclé correct
                        status=C_CYCLE_VRAI;
                        //sprintf(s_message,"x=%d y=%d Case du bas deja testée", x,y);
                        //trace(s_message,2,0);
                        //test_fin=1;
                    }

            }
            else
            {
                //pas de composante du bas
                //fin du test négatif
                status=C_CYCLE_FAUX;
                test_fin=2;
            }
        }
        else
        {
            //case pas dans le jeu
            //fin du test négatif
            status=C_CYCLE_FAUX;
            test_fin=2;
        }

    }

   if (test_fin !=0)
    {

        return status;
    }

    return status;

}
